import { useCallback, useEffect, useState } from "react";

declare global {
  interface Window {
    cpp_getGameState(): Promise<string>;
    cpp_setFieldState(
      stage: Stage,
      fieldName: string,
      value: string
    ): Promise<string>;
    cpp_setNextStage(): Promise<void>;
  }
}
export type Stage = 0 | 1 | 2 | 3 | 4;
export const NameStage = 0;
export const CredentialsStage = 1;
export const ExtrasStage = 2;
export const TxtCaptchaStage = 3;
export const ImageCaptchaStage = 4;

type Field = {
  value: string;
  errors: string[];
  disabled: boolean;
};

export type GameState = {
  stage: Stage;
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
        tsAndCs: Field;
      };
    },
    {
      imageURL: "";
      name: "txtcaptcha";
      state: {
        txtcaptcha: Field;
      };
    },
    {
      name: "imagecaptcha";
      images: string[];
      challengeText: string;
      state: {
        selected: number[];
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
    console.log({ newGameState: JSON.parse(newGameState) as GameState });
    setGameState(JSON.parse(newGameState) as GameState);
  }, []);

  const setFieldState = useCallback(
    async (stage: Stage, fieldName: string, value: string) => {
      await window.cpp_setFieldState(stage, fieldName, value);
    },
    []
  );

  const updateFieldState = useCallback(
    async (stage: Stage, fieldName: string, value: string) => {
      await setFieldState(stage, fieldName, value);
      await getGameState();
    },
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
