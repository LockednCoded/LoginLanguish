import TextField from "./TextField";
import { useLoginFlow } from "../scripts/login-flow";
import { ValidationBox } from "./ValidationBox";
import Modal from 'react-modal';
import { useState } from "react";
import { useBindings } from "../scripts/cpp-bindings";

export default function LoginPage() {
  // const loginFlow = useLoginFlow();
  // const fieldStates = loginFlow.fieldStates;

  const { fieldStates: fs, updateFieldState } = useBindings();

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

  return (
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
              <p>Prove you are who you say you are, {fs.firstName.value}.</p>
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
            value={fs.firstName.value}
            onChange={(e) => updateFieldState("firstName", e.target.value)}
            disabled={false}
            className="mt-3"
          />
          <TextField
            type="text"
            name="Last Name"
            value={fs.lastName.value}
            onChange={(e) => updateFieldState("lastName", e.target.value)}
            disabled={false}
            className="mt-3"
          />
        </div>
        <div className={`height-hidable  ${false ? "" : "height-hidden"}`}>
          <TextField
            type="text"
            name="Username"
            value={fs.username.value}
            onChange={(e) => updateFieldState("username", e.target.value)}
            className="mt-3"
          />
        </div>

        <div
          className={`height-hidable  ${
            true ? "" : "height-hidden"
            // TODO: replace this
          }`}
        >
          <div>
            <TextField
              type="password"
              name="Password"
              value={fs.password.value}
              onChange={(e) => updateFieldState("password", e.target.value)}
              className="mt-3 animate-height-in-container"
            />
            <ValidationBox
              shown={fs.password.error !== ""}
              message={fs.password.error}
              className="mt-3"
            />
          </div>
        </div>
        <div
          className={`height-hidable  ${
            true ? "" : "height-hidden"
            // TODO: replace this
          }`}
        >
          <div className="flex flex-row justify-between items-end ">
            <TextField
              type="date"
              value={fs.dob.value}
              name="Date of Birth"
              onChange={(e) => updateFieldState("dob", e.target.value)}
              className="mt-3 w-1/3"
            />

            <div className="mt-3">
              <input type="checkbox" name="terms" id="terms" />
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
                onChange={(e) => {
                  e.preventDefault();
                }}
              />
              <label className="text-gray-800 ml-2 font-light" htmlFor="terms">
                I want to recieve marketing emails
              </label>
            </div>
          </div>
        </div>

        <div className={`height-hidable  ${true ? "" : "height-hidden"}`}>
          <div>
            <TextField
              type="text"
              name="Verification"
              value={fs.txtcaptcha.value}
              onChange={(e) => updateFieldState("txtcaptcha", e.target.value)}
              className="mt-3"
            />
          </div>
        </div>

        <button
          className="bg-neutral-700 text-lg mt-12 text-white font-bold p-1 w-36 box-border rounded-md"
          type="button"
          onClick={() => {
            // if (loginFlow.stage === "txtcaptcha") openModal();
            // loginFlow.nextCallback();
          }}
        >
          Next
        </button>
      </form>
    </main>
  );
}
