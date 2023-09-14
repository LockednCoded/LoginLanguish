import TextField from "./TextField";
// import { useLoginFlow } from "../scripts/login-flow";
import { ValidationBox } from "./ValidationBox";
import Modal from "react-modal";
import { useState } from "react";
import {
  useBindings,
  NameStage,
  CredentialsStage,
  ExtrasStage,
  TxtcaptchaStage,
} from "../scripts/cpp-bindings";

export default function LoginPage() {
  // const loginFlow = useLoginFlow();
  // const fieldStates = loginFlow.fieldStates;

  const { gameState, updateFieldState, nextBtnClick } = useBindings();

  const [isModalOpen, setIsModalOpen] = useState(false);

  const openModal = () => {
    setIsModalOpen(true);
  };

  const closeModal = () => {
    setIsModalOpen(false);
  };

  const CaptchaImg = ({ source, onClick }) => {
    return (
      <div className="relative w-full h-full" onClick={onClick}>
        <img src={source} alt="Image" className="w-full h-full aspect-square" />
        <div className="absolute inset-0 bg-white opacity-0 transition-opacity duration-100 hover:opacity-50" />
      </div>
    );
  };

  const CaptchaSelect = (celeb) => {
    console.log(celeb + " clicked!");
  };

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
          <Modal
            id="img-captcha"
            isOpen={isModalOpen}
            contentLabel="Captcha Popup"
            appElement={document.getElementById("form")}
          >
            <div className="text-white bg-sky-400 absolute top-3 right-3 left-3 p-3">
              <button onClick={closeModal} className="absolute right-3">
                Close
              </button>
              <h1>Captcha</h1>
              <p>
                Prove you are who you say you are,{" "}
                {gameState.stages[NameStage].state.firstName.value}
              </p>
              <p>Select five Channing Tatums.</p>
            </div>
            <div className="absolute grid grid-cols-3 gap-1 bottom-5 left-5 right-5">
              <CaptchaImg
                source="bradpitt/brad_pitt_1.jpg"
                onClick={() => CaptchaSelect("Brad")}
              />
              <CaptchaImg
                source="bradpitt/brad_pitt_2."
                onClick={() => CaptchaSelect("Brad")}
              />
              <CaptchaImg
                source="channing/channing_tatum_1.jpg"
                onClick={() => CaptchaSelect("Channing")}
              />
              <CaptchaImg
                source="channing/channing_tatum_2.jpg"
                onClick={() => CaptchaSelect("Channing")}
              />
              <CaptchaImg
                source="bradpitt/brad_pitt_3.jpg"
                onClick={() => CaptchaSelect("Brad")}
              />
              <CaptchaImg
                source="channing/channing_tatum_3.jpg"
                onClick={() => CaptchaSelect("Channing")}
              />
              <CaptchaImg
                source="bradpitt/brad_pitt_4.jpg"
                onClick={() => CaptchaSelect("Brad")}
              />
              <CaptchaImg
                source="channing/channing_tatum_4.jpg"
                onClick={() => CaptchaSelect("Channing")}
              />
              <CaptchaImg
                source="channing/channing_tatum_5.jpg"
                onClick={() => CaptchaSelect("Channing")}
              />
            </div>
          </Modal>
          <TextField
            type="text"
            name="First Name"
            value={gameState.stages[NameStage].state.firstName.value}
            onChange={(e) =>
              updateFieldState(NameStage, "firstName", e.target.value)
            }
            disabled={false}
            className="mt-3"
          />
          <TextField
            type="text"
            name="Last Name"
            value={gameState.stages[NameStage].state.lastName.value}
            onChange={(e) =>
              updateFieldState(NameStage, "lastName", e.target.value)
            }
            disabled={false}
            className="mt-3"
          />
        </div>
        <div
          className={`height-hidable  ${
            gameState.stage >= CredentialsStage ? "" : "height-hidden"
          }`}
        >
          <TextField
            type="text"
            name="Username"
            value={gameState.stages[CredentialsStage].state.username.value}
            onChange={(e) =>
              updateFieldState(CredentialsStage, "username", e.target.value)
            }
            className="mt-3"
          />
          <ValidationBox
            shown={
              gameState.stages[CredentialsStage].state.username.errors.length >
              0
            }
            message={gameState.stages[CredentialsStage].state.username.errors}
            className="mt-3"
          />
          <div>
            <TextField
              type="password"
              name="Password"
              value={gameState.stages[CredentialsStage].state.password.value}
              onChange={(e) =>
                updateFieldState(CredentialsStage, "password", e.target.value)
              }
              className="mt-3 animate-height-in-container"
            />
            <ValidationBox
              shown={
                gameState.stages[CredentialsStage].state.password.errors
                  .length > 0
              }
              message={gameState.stages[CredentialsStage].state.password.errors}
              className="mt-3"
            />
          </div>
        </div>
        <div
          className={`height-hidable  ${
            gameState.stage >= ExtrasStage ? "" : "height-hidden"
          }`}
        >
          <div className="flex flex-row justify-between items-end ">
            <TextField
              type="date"
              name="Date of Birth"
              value={gameState.stages[ExtrasStage].state.dob.value}
              onChange={(e) =>
                updateFieldState(ExtrasStage, "dob", e.target.value)
              }
              className="mt-3 w-1/3"
            />

            <div className="mt-3">
              <input
                type="checkbox"
                name="terms"
                id="terms"
                checked={
                  gameState.stages[ExtrasStage].state.tsAndCs.value == "true"
                }
                onChange={(e) => {
                  updateFieldState(
                    ExtrasStage,
                    "tsAndCs",
                    e.target.checked ? "true" : "false"
                  );
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
            gameState.stage >= TxtcaptchaStage ? "" : "height-hidden"
          }`}
        >
          <div>
            <TextField
              type="text"
              name="Verification"
              value={gameState.stages[TxtcaptchaStage].state.txtcaptcha.value}
              onChange={(e) =>
                updateFieldState(TxtcaptchaStage, "txtcaptcha", e.target.value)
              }
              className="mt-3"
            />
          </div>
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
