import React from "react";
import { TxtCaptchaStage, useBindings } from "../scripts/useBindings";
import useSmoothUpdate from "../scripts/useSmoothUpdate";

export default function TextCaptcha({
  bindings,
  className,
}: {
  bindings: ReturnType<typeof useBindings>;
  className?: string;
}) {
  const { gameState, updateFieldState, stageProgress } = bindings;
  const [stableValue, updateValue, setFieldIsActive] = useSmoothUpdate(
    gameState.stages[TxtCaptchaStage].state.txtcaptcha.value,
    (val) => updateFieldState("txtcaptcha", "txtcaptcha", val)
  );
  return (
    <div className={className}>
      <label
        className="text-sm text-gray-800 font-light mb-0.5 block"
        htmlFor="textCaptcha"
      >
        Security Check
      </label>
      {gameState.stages[TxtCaptchaStage].state.captchaPassed ? (
        <p className="font-bold mt-1">Validated. You may proceed.</p>
      ) : (
        <div className="border rounded border-black w-full">
          <div
            className={`h-[125px] bg-center bg-contain bg-no-repeat`}
            style={{
              backgroundImage: `url('${gameState.stages[TxtCaptchaStage].state.imageURL}')`,
            }}
          ></div>
          <div className="bg-neutral-300 px-3 py-2">
            {gameState.stages[TxtCaptchaStage].state.lastRoundError ==
            "" ? null : (
              <p className="font-bold text-sm text-red-500 mb-2">
                {gameState.stages[TxtCaptchaStage].state.lastRoundError}
              </p>
            )}
            <p className="mb-2 text-sm">
              {gameState.stages[TxtCaptchaStage].state.challengeText}
            </p>
            <div className="flex flex-row">
              <input
                className="h-7 p-2 box-border rounded-md outline-none disabled:opacity-75 w-full text-sm select-text"
                data-test-id="text-field-text-captcha"
                type="text"
                name="textCaptcha"
                id="textCaptchaField"
                autoComplete="off"
                autoCorrect="off"
                autoCapitalize="off"
                spellCheck="false"
                placeholder="Enter answer"
                value={stableValue}
                onBlur={() => setFieldIsActive(false)}
                onFocus={() => setFieldIsActive(true)}
                onChange={(e) => updateValue(e.target.value)}
                disabled={
                  gameState.stages[TxtCaptchaStage].state.txtcaptcha.disabled
                }
              />
              <button
                className="text-sm rounded-md bg-white px-2 ml-2 font-bold h-7 box-border disabled:opacity-75 disabled:bg-ne"
                disabled={stableValue.length == 0}
                type="button"
                onClick={() => {
                  stageProgress("txtcaptcha");
                  updateValue("");
                }}
              >
                Submit
              </button>
            </div>
          </div>
        </div>
      )}
    </div>
  );
}
