import React from "react";
import { useState } from "react";

export function useLoginFlow() {
  const [stage, setStage] = useState(
    "name" as "name" | "credentials" | "details"
  );

  const [firstName, setFirstName] = useState("");
  const [lastName, setLastName] = useState("");
  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");
  const [dob, setDob] = useState("");

  const nextCallback = () => {
    if (stage === "name") setStage("credentials");
    if (stage === "credentials") setStage("details");
  };

  return {
    stage,
    nextCallback,
    fieldStates: {
      firstName: {
        value: firstName,
        onChange: (e: React.ChangeEvent<HTMLInputElement>) =>
          setFirstName(e.target.value),
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
    },
  };
}
