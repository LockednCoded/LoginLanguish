import { useEffect } from "react";
import {
  GameState,
  SetFieldStateFunc,
  Stage,
  StageName,
  TxtCaptchaStage,
  useBindings,
} from "../scripts/useBindings";
import useSmoothUpdate from "../scripts/useSmoothUpdate";

export default function TextCaptcha({
  bindings,
  className,
}: {
  bindings: ReturnType<typeof useBindings>;
  className?: string;
}) {
  const { gameState, updateFieldState } = bindings;
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
      <div className="border rounded border-black w-full">
        <div
          className={`h-[125px] bg-center bg-contain bg-no-repeat`}
          style={{
            backgroundImage: `url('${gameState.stages[TxtCaptchaStage].state.imageURL}')`,
          }}
        ></div>
        <div className="bg-neutral-300 px-3 py-2">
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
              onChange={updateValue}
              disabled={
                gameState.stages[TxtCaptchaStage].state.txtcaptcha.disabled
              }
            />
            <button
              className="text-sm rounded-md bg-white px-2 ml-2 font-bold h-7 box-border disabled:opacity-75"
              disabled={stableValue.length == 0}
              type="button"
            >
              Submit
            </button>
          </div>
        </div>
      </div>
    </div>
  );
}
