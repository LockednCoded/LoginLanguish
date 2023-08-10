import TextField from "./TextField";
import { useLoginFlow } from "../scripts/login-flow";
import { ValidationBox } from "./ValidationBox";
import Modal from 'react-modal';
import { useState } from "react";

export default function LoginPage() {
  const loginFlow = useLoginFlow();
  const fieldStates = loginFlow.fieldStates;

  const [isModalOpen, setIsModalOpen] = useState(false);

  const openModal = () => {
    setIsModalOpen(true);
  };
  
  const closeModal = () => {
    setIsModalOpen(false);
  };

  return (
    <main className="flex flex-col justify-center items-center w-[64rem] h-[42rem] bg-white border-2 rounded-sm border-gray-400">
      <h1 className="text-2xl m-0">Please register an account to continue</h1>
      <form
        className={`mt-12 ${
          loginFlow.stage == "name" ? "w-[20rem]" : "w-[30rem]"
        } transition-all duration-300
				`}
      >
        <div
          className={`grid gap-x-3.5 ${
            loginFlow.stage !== "name" ? "grid-cols-2" : ""
          }`}
        >
          <div id='pop-up'>
            <button onClick={openModal} type="button">Open Popup</button>
            <Modal
              id='img-captcha'
              isOpen={isModalOpen}
              //onRequestClose={closeModal}
              contentLabel="Captcha Popup"
              appElement={document.getElementById('pop-up')}
            >
              <h1>Captcha</h1>
              <p>Prove you are who you say you are, {fieldStates.firstName.value}.</p>
              <p>Select five Channing Tatums.</p>
              <button onClick={closeModal} className="absolute top-5 right-5">Close</button>
            </Modal>
          </div>
          <TextField
            type="text"
            name="First Name"
            value={fieldStates.firstName.value}
            onChange={fieldStates.firstName.onChange}
            disabled={fieldStates.firstName.disabled}
            className="mt-3"
          />
          <TextField
            type="text"
            name="Last Name"
            value={fieldStates.lastName.value}
            onChange={fieldStates.lastName.onChange}
            disabled={fieldStates.firstName.disabled}
            className="mt-3"
          />
        </div>
        <div
          className={`height-hidable  ${
            fieldStates.username.visible ? "" : "height-hidden"
          }`}
        >
          <TextField
            type="text"
            name="Username"
            value={fieldStates.username.value}
            onChange={fieldStates.username.onChange}
            className="mt-3"
          />
        </div>

        <div
          className={`height-hidable  ${
            fieldStates.password.visible ? "" : "height-hidden"
          }`}
        >
          <div>
            <TextField
              type="password"
              name="Password"
              value={fieldStates.password.value}
              onChange={fieldStates.password.onChange}
              className="mt-3 animate-height-in-container"
            />
            <ValidationBox
              shown={fieldStates.password.validationIssue !== ""}
              message={fieldStates.password.validationIssue}
              className="mt-3"
            />
          </div>
        </div>
        <div
          className={`height-hidable  ${
            fieldStates.dob.visible ? "" : "height-hidden"
          }`}
        >
          <div className="flex flex-row justify-between items-end ">
            <TextField
              type="date"
              value={fieldStates.dob.value}
              name="Date of Birth"
              onChange={fieldStates.dob.onChange}
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
        <button
          className="bg-neutral-700 text-lg mt-12 text-white font-bold p-1 w-36 box-border rounded-md"
          type="button"
          onClick={loginFlow.nextCallback}
        >
          Next
        </button>
      </form>
    </main>
  );
}
