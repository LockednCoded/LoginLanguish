import { useCallback, useEffect, useState } from "react";

declare global {
  interface Window {
    cpp_getGameState(): Promise<string>;
    cpp_setFieldState: SetFieldStateFunc;
    cpp_setNextStage(): Promise<void>;
  }
}

export type SetFieldStateFunc = (
  stage: StageName,
  fieldName: string,
  value: string | boolean | string[]
) => Promise<void>;

export type Stage = 0 | 1 | 2 | 3 | 4;
export type StageName =
  | "name"
  | "credentials"
  | "extras"
  | "txtcaptcha"
  | "imagecaptcha";
export const NameStage = 0;
export const CredentialsStage = 1;
export const ExtrasStage = 2;
export const TxtCaptchaStage = 3;
export const ImageCaptchaStage = 4;
export const StageMap = {
  name: NameStage,
  credentials: CredentialsStage,
  extras: ExtrasStage,
  txtcaptcha: TxtCaptchaStage,
  imagecaptcha: ImageCaptchaStage,
};

type Field = {
  value: string;
  errors: string[];
  disabled: boolean;
};

export type GameState = {
  stage: StageName;
  canProgress: boolean;
  stages: [
    {
      name: "name";
      state: {
        firstName: Field;
        lastName: Field;
      };
    },
    {
      name: "credentials";
      state: {
        username: Field;
        password: Field;
      };
    },
    {
      name: "extras";
      state: {
        dob: Field;
        tsAndCs: {
          value: boolean;
          errors: string[];
          disabled: boolean;
        };
      };
    },
    {
      name: "txtcaptcha";
      state: {
        imageURL: "";
        txtcaptcha: Field;
        challengeText: string;
      };
    },
    {
      name: "imagecaptcha";
      state: {
        selected: string[];
        images: string[];
        challengeText: string;
      };
    }
  ];
};

export function useBindings() {
  const [gameState, setGameState] = useState<GameState>(null);

  useEffect(() => {
    getGameState();
  }, []);

  const getGameState = useCallback(async () => {
    const newGameState = atob(await window.cpp_getGameState());
    setGameState(JSON.parse(newGameState) as GameState);
  }, []);

  const setFieldState = useCallback(
    (async (
      stage: StageName,
      fieldName: string,
      value: string | boolean | string[]
    ) => {
      // const encodedValue =
      //   typeof value === "string"
      //     ? encodeURIComponent(value)
      //     : typeof value == "object"
      //     ? value.map((val) => encodeURIComponent(val))
      //     : value;
      console.log(value);

      await window.cpp_setFieldState(stage, fieldName, value);
    }) as SetFieldStateFunc,
    []
  );

  const updateFieldState = useCallback(
    (async (
      stage: StageName,
      fieldName: string,
      value: string | boolean | string[]
    ) => {
      await setFieldState(stage, fieldName, value);
      await getGameState();
    }) as SetFieldStateFunc,
    []
  );
  const nextBtnClick = useCallback(async () => {
    await window.cpp_setNextStage();
    await getGameState();
  }, []);

  return {
    gameState,
    setFieldState,
    updateFieldState,
    nextBtnClick,
  };
}
