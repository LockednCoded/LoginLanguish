import React from "react";
import { ImageCaptchaStage, useBindings } from "../scripts/useBindings";

const CaptchaTile = ({
  source,
  onClick,
  selected,
  label,
}: {
  source: string;
  onClick: () => any;
  selected: boolean;
  label: string;
}) => {
  return (
    <div
      className={`relative transition-all ${
        selected ? "scale-95 border-blue-600 border-[5px]" : ""
      }`}
      onClick={onClick}
      data-test-id="image-captcha-tile-div-${source}"
    >
      <div className="absolute bg-white opacity-0 transition-opacity duration-100 hover:opacity-50 w-full h-full" />
      <img src={source} alt="Image" className="w-full h-full aspect-square" />
      <div className="absolute bottom-1 font-bold text-sm">{label}</div>
    </div>
  );
};

export default function ImageCaptcha({
  bindings,
}: {
  bindings: ReturnType<typeof useBindings>;
}) {
  const { gameState, updateFieldState, stageProgress } = bindings;
  return (
    <div className="bg-gray-950/25 fixed z-10 h-full w-full top-0 left-0 flex items-center justify-center">
      <div className="bg-white p-1">
        <div className="text-white bg-blue-600 p-3 mb-1 flex flex-col">
          {gameState.stages[ImageCaptchaStage].state.lastRoundError ==
          "" ? null : (
            <h1 className="font-bold text-lg text-red-500">
              {gameState.stages[ImageCaptchaStage].state.lastRoundError}
            </h1>
          )}
          <h1 className="font-bold text-xl">
            {gameState.stages[ImageCaptchaStage].state.challengeText}
          </h1>
        </div>
        <div className="grid grid-cols-3 gap-1 w-[400px] h-[400px]">
          {gameState.stages[ImageCaptchaStage].state.images.map((image, i) => {
            const selected =
              gameState.stages[ImageCaptchaStage].state.selected.includes(
                image
              );
            const updateVersion = selected
              ? gameState.stages[ImageCaptchaStage].state.selected.filter(
                  (v) => v !== image
                )
              : [...gameState.stages[ImageCaptchaStage].state.selected, image];

            return (
              <CaptchaTile
                data-test-id="image-captcha-tile-${image}"
                source={image}
                label={
                  gameState.stages[ImageCaptchaStage].state.imageLabels[i] ?? ""
                }
                onClick={() =>
                  updateFieldState("imagecaptcha", "selected", updateVersion)
                }
                selected={selected}
              />
            );
          })}
        </div>
        <div className="flex justify-end mt-1">
          <button
            className="bg-blue-600 text-lg text-white font-bold p-1 w-36"
            type="button"
            disabled={false}
            data-test-id="image-captcha-verify-btn"
            onClick={() => {
              stageProgress("imagecaptcha");
            }}
          >
            Verify
          </button>
        </div>
      </div>
    </div>
  );
}
