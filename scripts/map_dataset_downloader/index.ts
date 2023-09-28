import ProgressBar from "progress";
import puppeteer, { Browser, ElementHandle } from "puppeteer";
import pLimit from "p-limit";
import fs from "fs";
import Path from "path";
import axios from "axios";
import { createObjectCsvWriter } from "csv-writer";

main();

//I should have used R

async function main() {
  // Launch the browser and open a new blank page
  const browser = await puppeteer.launch({ headless: "new" });

  const countryListings = await getCountryListings(browser);
  await saveCountriesCSV(countryListings);

  let bar = new ProgressBar(
    "Finding Image links: [:bar] :percent :etas :token1",
    {
      total: countryListings.length,
      width: 30,
    }
  );

  const limit = pLimit(5);
  let countries = await Promise.all(
    countryListings.map(async (country) =>
      limit(async () => {
        try {
          const map = await getMap(browser, country.link);
          return { ...country, map };
        } finally {
          bar.tick({
            token1: country.name,
          });
        }
      })
    )
  );
  bar.terminate();

  bar = new ProgressBar("Downloading Images: [:bar] :percent :etas :token1", {
    total: countries.length,
    width: 30,
  });

  countries.forEach((country) => {
    limit(async () => {
      await downloadImage(
        country.map,
        Path.resolve(import.meta.dir, "data", "images", country.name + ".png")
      );
      bar.tick({
        token1: country.name,
      });
    });
  });
  bar.terminate();

  await browser.close();
}

async function getCountryListings(browser: Browser) {
  const page = await browser.newPage();

  // Navigate the page to a URL
  await page.goto(
    // "https://en.wikipedia.org/wiki/List_of_countries_and_dependencies_by_population"
    "https://en.wikipedia.org/wiki/The_Economist_Democracy_Index"
  );

  const tableBodySelctor = ".wikitable:nth-of-type(5) tbody";
  await page.waitForSelector(tableBodySelctor);

  const tableBody = await page.$(tableBodySelctor);
  if (tableBody == null) throw new Error("No table body found");
  const rawRows = await tableBody.$$("tr");
  const countryListings = await Promise.all(
    rawRows.map(async (row, i) => {
      const [name, link, regime] = await row.evaluate((el) => {
        const ofst = el.children.length >= 19 ? 1 : 0;
        return [
          el.children[1 + ofst].textContent.trim(),
          el.children[1 + ofst].querySelector("a").href,
          el.children[2 + ofst].textContent.trim(),
        ];
      });
      return { name, link, regime };
    })
  );

  await page.close();

  return countryListings;
}

async function getMap(browser: Browser, url: string) {
  const page = await browser.newPage();
  await page.goto(url);
  const infoBox = await page.$(".infobox");
  if (infoBox == null) throw new Error("No info box found");

  let mapImageSrc: string;
  try {
    mapImageSrc = await getMapFromStructure(infoBox);
  } catch (e) {
    mapImageSrc = await getMapFromKeywords(infoBox);
  }

  await page.close();
  return mapImageSrc;
}

async function getMapFromStructure(infoBox: ElementHandle) {
  const mapCaption = await infoBox.$(".ib-country-map-caption");
  if (mapCaption == null) throw new Error("No map caption found");
  const maptd = (await mapCaption.evaluateHandle((el) =>
    el.closest("td")
  )) as ElementHandle;
  if (maptd == null) throw new Error("No map td found");
  const mapImg = await maptd.$("img");
  if (mapImg == null) throw new Error("No map found");

  return await mapImg.evaluate((el) => el.src);
}

const mapKeywords = ["map", "orthographic", "globe", "location"];
const mapBlacklist = ["maple"];
async function getMapFromKeywords(infoBox: ElementHandle) {
  const links = await infoBox.$$("a");
  const mapLinks = await Promise.all(
    links.map(async (link) => {
      const image = await link.$("img");
      if (image == null) return null;
      const imageSrc = (await image.evaluate((el) => el.src)) as string;
      const imageAlt = (await image.evaluate((el) => el.alt)) as string;
      const href = (await link.evaluate((el) => el.href)) as string;
      return { image, imageSrc, imageAlt, href };
    })
  );
  const mapLinksFiltered = mapLinks.filter((link) => link != null) as {
    image: ElementHandle;
    imageSrc: string;
    imageAlt: string;
    href: string;
  }[];
  const mapLink = mapLinksFiltered.find(({ imageSrc, imageAlt, href }) => {
    return (
      mapKeywords.some((keyword) =>
        [imageSrc, imageAlt, href].some((text) =>
          text?.toLowerCase().includes(keyword)
        )
      ) &&
      mapBlacklist.every((keyword) =>
        [imageSrc, imageAlt, href].every(
          (text) => !text?.toLowerCase().includes(keyword)
        )
      )
    );
  });
  if (mapLink == null) throw new Error("No map found");
  return mapLink.imageSrc;
}
async function downloadImage(imageUrl: string, path: string) {
  const response = await axios({
    method: "GET",
    url: imageUrl,
    responseType: "stream",
  });
  response.data.pipe(fs.createWriteStream(path));

  await new Promise((resolve, reject) => {
    response.data.on("end", () => {
      resolve("Done");
    });

    response.data.on("error", () => {
      reject();
    });
  });
}
async function saveCountriesCSV(
  countryListings: { name: string; link: string; regime: any }[]
) {
  const csvWriter = createObjectCsvWriter({
    path: Path.resolve(import.meta.dir, "data", "_country_data.csv"),
    header: [
      { id: "name", title: "Name" },
      { id: "link", title: "Link" },
      { id: "regime", title: "Regime" },
    ],
  });
  await csvWriter.writeRecords(countryListings);
}
