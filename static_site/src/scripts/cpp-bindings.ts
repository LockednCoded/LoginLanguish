import { useCallback, useState } from "react";

declare global {
  interface Window {
    cpp_getFieldStates(): Promise<string>;
    cpp_updateFieldState(field: string, value: string): Promise<string>;
  }
}

type Field = {
  value: string;
  error: string;
  // disabled: boolean;
};

type FieldKeys =
  | "firstName"
  | "lastName"
  | "username"
  | "password"
  | "dob"
  | "txtcaptcha";

type FieldState = {
  [fieldKey in FieldKeys]: Field;
} & {
  __serialized: string;
};

const emptyFieldState = Object.fromEntries([
  ...["firstName", "lastName", "username", "password", "dob", "txtcaptcha"].map(
    (field) => [
      field,
      {
        value: "",
        error: "",
        // disabled: false,
      },
    ]
  ),
  ["__serialized", ""],
]) as FieldState;

export function useBindings() {
  const [fieldStates, setFieldStates] = useState(emptyFieldState);

  const updateFieldStates = useCallback(async () => {
    const newFieldStateJSON = atob(await window.cpp_getFieldStates());
    console.log(newFieldStateJSON);
    if (newFieldStateJSON === fieldStates.__serialized) return;
    const newFieldState = {
      ...fieldStates,
      ...JSON.parse(newFieldStateJSON),
      __serialized: newFieldStateJSON,
    } as FieldState;
    console.log(newFieldState);
    setFieldStates(newFieldState);
  }, [fieldStates.__serialized]);

  const updateFieldState = useCallback(
    async (field: keyof FieldState, value: string) => {
      if (atob(await window.cpp_updateFieldState(field, value)) == "true") {
        await updateFieldStates();
      }
    },
    [updateFieldStates]
  );

  return {
    fieldStates,
    updateFieldState,
  };
}
