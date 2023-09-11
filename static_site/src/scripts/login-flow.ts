import React from "react";
import { useState } from "react";
import { useBindings } from "./cpp-bindings";

export function useLoginFlow() {
  const [stage, setStage] = useState(
    "name" as "name" | "credentials" | "details" | "txtcaptcha"
  );

  const [firstName, setFirstName] = useState("");
  const [lastName, setLastName] = useState("");
  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");
  const [dob, setDob] = useState("");
  const [txtcaptcha, setCaptcha] = useState("");

  const nextCallback = () => {
    if (stage === "name") setStage("credentials");
    if (stage === "credentials") setStage("details");
    if (stage === "details") setStage("txtcaptcha");
  };

  const bindings = useBindings();

  return {
    stage,
    nextCallback,
    fieldStates: {
      firstName: {
        value: firstName,
        onChange: (e: React.ChangeEvent<HTMLInputElement>) => {
          setFirstName(e.target.value),
            bindings.updateFieldState("firstName", e.target.value);
        },
        disabled: stage !== "name",
      },
      lastName: {
        value: lastName,
        onChange: (e: React.ChangeEvent<HTMLInputElement>) =>
          setLastName(e.target.value),
        disabled: stage !== "name",
      },
      username: {
        value: username,
        onChange: (e: React.ChangeEvent<HTMLInputElement>) =>
          setUsername(e.target.value),
        visible: stage !== "name",
        validationIssue: "",
      },
      password: {
        value: password,
        onChange: (e: React.ChangeEvent<HTMLInputElement>) =>
          setPassword(e.target.value),
        visible: stage !== "name",
        validationIssue:
          password.length > 0 && !/[^a-zA-Z0-9 ]/.test(password)
            ? "Your password must contain at least one symbol"
            : "",
      },
      dob: {
        value: dob,
        onChange: (e: React.ChangeEvent<HTMLInputElement>) => {
          console.log(e.target.value);

          setDob(e.target.value);
        },
        visible: stage === "details",
        validationIssue: "",
      },
      txtcaptcha: {
        value: txtcaptcha,
        onChange: (e: React.ChangeEvent<HTMLInputElement>) => {
          console.log(e.target.value);
          setCaptcha(e.target.value);
        },
        visible: stage === "txtcaptcha",
        validationIssue: "",
      },
    },
  };
}
