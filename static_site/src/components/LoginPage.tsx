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
import { useState } from "react";
import TermsAndConditions from "./TermsAndConditions";

export default function LoginPage() {
  const bindings = useBindings();
  const { gameState, updateFieldState, nextBtnClick, stageProgress } = bindings;
  const [tsAndCsOpen, setTsAndCsOpen] = useState(false);

  return gameState == null ? null : (
    <main className="flex flex-col justify-center w-full h-full bg-white rounded-sm select-none">
      <div className="overflow-y-scroll">
        <div className="py-14 flex flex-col items-center box-border">
          <h1 className="text-2xl m-0">
            Please register an account to continue
          </h1>
          <form
            id="form"
            className={`mt-12 ${
              StageMap[gameState.stage] > NameStage ? "w-[30rem]" : "w-[20rem]"
            } transition-all duration-300
				`}
          >
            <div
              className={`grid gap-x-3.5 ${
                StageMap[gameState.stage] > NameStage ? "grid-cols-2" : ""
              }`}
            >
              {StageMap[gameState.stage] == ImageCaptchaStage && (
                <ImageCaptcha bindings={bindings} />
              )}
              <TextField
                type="text"
                name="First Name"
                value={gameState.stages[NameStage].state.firstName.value}
                onChange={(newVal) =>
                  updateFieldState("name", "firstName", newVal)
                }
                disabled={gameState.stages[NameStage].state.firstName.disabled}
                className="mt-3"
              />
              <TextField
                type="text"
                name="Last Name"
                value={gameState.stages[NameStage].state.lastName.value}
                onChange={(newVal) =>
                  updateFieldState("name", "lastName", newVal)
                }
                disabled={gameState.stages[NameStage].state.lastName.disabled}
                className="mt-3"
              />
              <ValidationBox
                messages={gameState.stages[NameStage].state.firstName.errors}
                className="mt-3"
              />
              <ValidationBox
                messages={gameState.stages[NameStage].state.lastName.errors}
                className="mt-3"
              />
            </div>
            <div
              className={`height-hidable  ${
                StageMap[gameState.stage] >= CredentialsStage
                  ? ""
                  : "height-hidden"
              }`}
            >
              <TextField
                type="text"
                name="Username"
                value={gameState.stages[CredentialsStage].state.username.value}
                onChange={(newVal) =>
                  updateFieldState("credentials", "username", newVal)
                }
                disabled={
                  gameState.stages[CredentialsStage].state.username.disabled
                }
                className="mt-3"
              />
              <ValidationBox
                messages={
                  gameState.stages[CredentialsStage].state.username.errors
                }
                className="mt-3"
              />
              <div>
                <TextField
                  type="password"
                  name="Password"
                  value={
                    gameState.stages[CredentialsStage].state.password.value
                  }
                  onChange={(newVal) =>
                    updateFieldState("credentials", "password", newVal)
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
                  value={gameState.stages[ExtrasStage].state.dob.value
                    .reverse()
                    .map((n) => n.toString().padStart(2, "0"))
                    .join("-")}
                  onChange={(newVal) => {
                    const dateArray = newVal
                      .split("-")
                      .reverse()
                      .map((num) => Number.parseInt(num));
                    updateFieldState("extras", "dob", dateArray);
                  }}
                  disabled={gameState.stages[ExtrasStage].state.dob.disabled}
                  className="mt-3 w-1/3"
                />

                <div className="mt-3">
                  <input
                    type="checkbox"
                    name="terms"
                    id="terms"
                    checked={gameState.stages[ExtrasStage].state.tsAndCs.value}
                    disabled={
                      gameState.stages[ExtrasStage].state.tsAndCs.disabled
                    }
                    onChange={(e) => {
                      updateFieldState("extras", "tsAndCs", e.target.checked);
                    }}
                  />
                  <label
                    className="text-gray-800 ml-2 font-light"
                    htmlFor="terms"
                  >
                    I agree to the{" "}
                    <button
                      className="text-blue-400"
                      type="button"
                      onClick={() => setTsAndCsOpen(true)}
                    >
                      terms & conditions
                    </button>
                  </label>
                  {tsAndCsOpen && (
                    <TermsAndConditions
                      onRequestClose={() => setTsAndCsOpen(false)}
                    />
                  )}
                  <br />
                  <input
                    type="checkbox"
                    name="terms"
                    id="marketing"
                    checked
                    onChange={(e) => e.preventDefault()}
                  />
                  <label
                    className="text-gray-800 ml-2 font-light"
                    htmlFor="terms"
                  >
                    I want to recieve marketing emails
                  </label>
                </div>
              </div>
              <ValidationBox
                messages={gameState.stages[ExtrasStage].state.dob.errors}
                className="mt-3"
              />
              <ValidationBox
                messages={gameState.stages[ExtrasStage].state.tsAndCs.errors}
                className="mt-3"
              />
            </div>

            <div
              className={`height-hidable  ${
                StageMap[gameState.stage] >= TxtCaptchaStage
                  ? ""
                  : "height-hidden"
              }`}
            >
              <TextCaptcha bindings={bindings} className="mt-3" />
            </div>

            <button
              className="bg-neutral-700 text-lg mt-12 text-white font-bold p-1 w-36 box-border rounded-md disabled:text-gray-400"
              type="button"
              disabled={!gameState.canProgress}
              onClick={() => {
                nextBtnClick();
              }}
            >
              Next
            </button>
          </form>
        </div>
      </div>
    </main>
  );
}
