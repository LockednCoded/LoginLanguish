import TextField from "./TextField";
// import { useLoginFlow } from "../scripts/login-flow";
import { ValidationBox } from "./ValidationBox";
// import Modal from "react-modal";
import {
  useBindings,
  NameStage,
  CredentialsStage,
  ExtrasStage,
  TxtCaptchaStage,
  ImageCaptchaStage,
  StageMap,
} from "../scripts/useBindings";
import ImageCaptcha from "./ImageCaptcha";
import TextCaptcha from "./TextCaptcha";

export default function LoginPage() {
  const { gameState, updateFieldState, nextBtnClick } = useBindings();

  return gameState == null ? null : (
    <main className="flex flex-col justify-center items-center w-[64rem] h-[42rem] bg-white border-2 rounded-sm border-gray-400">
      <h1 className="text-2xl m-0">Please register an account to continue</h1>
      <form
        id="form"
        className={`mt-12 ${
          false ? "w-[20rem]" : "w-[30rem]"
        } transition-all duration-300
				`}
      >
        <div className={`grid gap-x-3.5 ${true ? "grid-cols-2" : ""}`}>
          {StageMap[gameState.stage] == ImageCaptchaStage && (
            <ImageCaptcha
              gameState={gameState}
              updateFieldState={updateFieldState}
              nextBtnClick={nextBtnClick}
            />
          )}
          <TextField
            type="text"
            name="First Name"
            value={gameState.stages[NameStage].state.firstName.value}
            onChange={(e) =>
              updateFieldState("name", "firstName", e.target.value)
            }
            disabled={gameState.stages[NameStage].state.firstName.disabled}
            className="mt-3"
          />
          <TextField
            type="text"
            name="Last Name"
            value={gameState.stages[NameStage].state.lastName.value}
            onChange={(e) =>
              updateFieldState("name", "lastName", e.target.value)
            }
            disabled={gameState.stages[NameStage].state.lastName.disabled}
            className="mt-3"
          />
        </div>
        <div
          className={`height-hidable  ${
            StageMap[gameState.stage] >= CredentialsStage ? "" : "height-hidden"
          }`}
        >
          <TextField
            type="text"
            name="Username"
            value={gameState.stages[CredentialsStage].state.username.value}
            onChange={(e) =>
              updateFieldState("credentials", "username", e.target.value)
            }
            disabled={
              gameState.stages[CredentialsStage].state.username.disabled
            }
            className="mt-3"
          />
          <ValidationBox
            messages={gameState.stages[CredentialsStage].state.username.errors}
            className="mt-3"
          />
          <div>
            <TextField
              type="password"
              name="Password"
              value={gameState.stages[CredentialsStage].state.password.value}
              onChange={(e) =>
                updateFieldState("credentials", "password", e.target.value)
              }
              disabled={
                gameState.stages[CredentialsStage].state.password.disabled
              }
              className="mt-3 animate-height-in-container"
            />
            <ValidationBox
              messages={
                gameState.stages[CredentialsStage].state.password.errors
              }
              className="mt-3"
            />
          </div>
        </div>
        <div
          className={`height-hidable  ${
            StageMap[gameState.stage] >= ExtrasStage ? "" : "height-hidden"
          }`}
        >
          <div className="flex flex-row justify-between items-end ">
            <TextField
              type="date"
              name="Date of Birth"
              value={gameState.stages[ExtrasStage].state.dob.value}
              onChange={(e) =>
                updateFieldState("extras", "dob", e.target.value)
              }
              disabled={gameState.stages[ExtrasStage].state.dob.disabled}
              className="mt-3 w-1/3"
            />

            <div className="mt-3">
              <input
                type="checkbox"
                name="terms"
                id="terms"
                checked={gameState.stages[ExtrasStage].state.tsAndCs.value}
                disabled={gameState.stages[ExtrasStage].state.tsAndCs.disabled}
                onChange={(e) => {
                  updateFieldState("extras", "tsAndCs", e.target.checked);
                }}
              />
              <label className="text-gray-800 ml-2 font-light" htmlFor="terms">
                I agree to the{" "}
                <a className="text-blue-400" href="#">
                  terms & conditions
                </a>
              </label>
              <br />
              <input
                type="checkbox"
                name="terms"
                id="marketing"
                checked
                onChange={(e) => e.preventDefault()}
              />
              <label className="text-gray-800 ml-2 font-light" htmlFor="terms">
                I want to recieve marketing emails
              </label>
            </div>
          </div>
        </div>

        <div
          className={`height-hidable  ${
            StageMap[gameState.stage] >= TxtCaptchaStage ? "" : "height-hidden"
          }`}
        >
          <TextCaptcha
            gameState={gameState}
            updateFieldState={updateFieldState}
            nextBtnClick={nextBtnClick}
          />
        </div>

        <button
          className="bg-neutral-700 text-lg mt-12 text-white font-bold p-1 w-36 box-border rounded-md"
          type="button"
          disabled={!gameState.canProgress}
          onClick={() => {
            nextBtnClick();
          }}
        >
          Next
        </button>
      </form>
    </main>
  );
}
