import React from "react";
import TextField from "./TextField";
import { useLoginFlow } from "../scripts/login-flow";
import { ValidationBox } from "./ValidationBox";

export default function LoginPage() {
  const loginFlow = useLoginFlow();
  const fieldStates = loginFlow.fieldStates;

  return (
    <main className="flex flex-col justify-center items-center w-[64rem] h-[42rem] bg-white border-2 rounded-sm border-gray-400">
      <h1 className="text-2xl m-0">Please register an account to continue</h1>
      <form
        className={`mt-12 ${
          loginFlow.stage == "name" ? "w-[20rem]" : "w-[30rem]"
        } transition-all
				`}
      >
        <div
          className={`grid gap-x-3.5 ${
            loginFlow.stage !== "name" ? "grid-cols-2" : ""
          }`}
        >
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
        {fieldStates.username.visible && (
          <TextField
            type="text"
            name="Username"
            value={fieldStates.username.value}
            onChange={fieldStates.username.onChange}
            className="mt-3"
          />
        )}
        {fieldStates.password.visible && (
          <>
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
          </>
        )}
        {fieldStates.dob.visible && (
          <div className="flex flex-row justify-between items-end">
            <TextField
              type="date"
              value={fieldStates.dob.value}
              name="Date of Birth"
              onChange={fieldStates.dob.onChange}
              className="mt-3 w-1/3"
            />

            <div className="mt-3">
              <input
                type="checkbox"
                name="terms"
                id="terms"
                data-test-id="terms-checkbox"
              />
              <label className="text-gray-800 ml-2 font-light" htmlFor="terms">
                I agree to the{" "}
                <a className="text-blue-400" href="#" data-test-id="ts-and-cs">
                  terms & conditions
                </a>
              </label>
              <br />
              <input
                type="checkbox"
                data-test-id="marketing-checkbox"
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
        )}
        <button
          className="bg-neutral-700 text-lg mt-12 text-white font-bold p-1 w-36 box-border rounded-md"
          type="button"
          data-test-id="next-button"
          onClick={loginFlow.nextCallback}
        >
          Next
        </button>
      </form>
    </main>
  );
}
