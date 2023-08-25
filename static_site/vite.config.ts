import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";
import Icons from "unplugin-icons/vite";
import { viteSingleFile } from "vite-plugin-singlefile";

export default defineConfig({
  base: "",
  root: "src",
  build: {
    outDir: "../dist",
    target: "es2015",
    minify: false,
  },
  plugins: [
    react(),
    Icons({
      autoInstall: true,
      compiler: "jsx",
      jsx: "react",
    }),
    viteSingleFile(),
  ],
});
