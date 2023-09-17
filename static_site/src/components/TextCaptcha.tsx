import { useEffect } from "react";
import {
  GameState,
  SetFieldStateFunc,
  Stage,
  StageName,
  TxtCaptchaStage,
} from "../scripts/useBindings";
import useSmoothUpdate from "../scripts/useSmoothUpdate";

export default function TextCaptcha({
  gameState,
  updateFieldState,
  nextBtnClick,
  className,
}: {
  gameState: GameState;
  updateFieldState: SetFieldStateFunc;
  nextBtnClick: () => Promise<void>;
  className?: string;
}) {
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
        </div>
      </div>
    </div>
  );
}
