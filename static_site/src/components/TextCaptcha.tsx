import {
  GameState,
  SetFieldStateFunc,
  Stage,
  StageName,
  TxtCaptchaStage,
} from "../scripts/useBindings";

export default function TextCaptcha({
  gameState,
  updateFieldState,
  nextBtnClick,
}: {
  gameState: GameState;
  updateFieldState: SetFieldStateFunc;
  nextBtnClick: () => Promise<void>;
}) {
  return (
    <div>
      <label
        className="text-sm text-gray-800 font-light mb-0.5 block"
        htmlFor="textCaptcha"
      >
        Security Check
      </label>
      <div className="border rounded border-black w-full">
        <div className="h-[125px]"></div>
        <div className="bg-gray-400">
          <input
            className="h-9 p-2 box-border outline-none disabled:opacity-75"
            data-test-id="text-field-text-captcha"
            type="text"
            name="textCaptcha"
            id="textCaptchaField"
            autoComplete="off"
            value={gameState.stages[TxtCaptchaStage].state.txtcaptcha.value}
            onChange={(e) =>
              updateFieldState("txtcaptcha", "txtcaptcha", e.target.value)
            }
            disabled={
              gameState.stages[TxtCaptchaStage].state.txtcaptcha.disabled
            }
          />
        </div>
      </div>
    </div>
  );
}
