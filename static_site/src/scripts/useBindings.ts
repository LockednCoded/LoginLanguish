import { useCallback, useEffect, useState } from "react";

declare global {
  // eslint-disable-next-line @typescript-eslint/no-unused-vars (Because Window is actually used)
  interface Window {
    cpp_getGameState(): Promise<string>;
    cpp_setFieldState: SetFieldStateFunc;
    cpp_setNextStage(): Promise<void>;
    cpp_stageProgress(_sn: StageName): Promise<void>;
  }
}

export type SetFieldStateFunc = (
  _stage: StageName,
  _fieldName: string,
  _value: FieldValue
) => Promise<void>;

type FieldValue = string | boolean | string[] | number[];

export type Stage = 0 | 1 | 2 | 3 | 4 | 5;
export type StageName =
  | "name"
  | "credentials"
  | "extras"
  | "txtcaptcha"
  | "imagecaptcha"
  | "end";
export const NameStage = 0;
export const CredentialsStage = 1;
export const ExtrasStage = 2;
export const TxtCaptchaStage = 3;
export const ImageCaptchaStage = 4;
export const EndStage = 5;
export const StageMap = {
  name: NameStage,
  credentials: CredentialsStage,
  extras: ExtrasStage,
  txtcaptcha: TxtCaptchaStage,
  imagecaptcha: ImageCaptchaStage,
  end: EndStage,
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
        dob: {
          value: number[]; //[Day, Month, Year]
          errors: string[];
          disabled: boolean;
        };
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
        captchaPassed: boolean;
        lastRoundError: string;
        tallImage: boolean;
      };
    },
    {
      name: "imagecaptcha";
      state: {
        selected: string[];
        lastRoundError: string;
        images: string[];
        challengeText: string;
      };
    },
    {
      name: "end";
      state: {};
    }
  ];
};

export function useBindings() {
  const [gameState, setGameState] = useState<GameState>(null);

  const getGameState = useCallback(async () => {
    const newGameState = atob(await window.cpp_getGameState());
    setGameState(JSON.parse(newGameState) as GameState);
  }, [setGameState]);

  useEffect(() => {
    getGameState();
  }, [getGameState]);

  const setFieldState = (async (
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

    await window.cpp_setFieldState(stage, fieldName, value);
  }) as SetFieldStateFunc;

  const updateFieldState = (async (
    stage: StageName,
    fieldName: string,
    value: FieldValue
  ) => {
    await setFieldState(stage, fieldName, value);
    await getGameState();
  }) as SetFieldStateFunc;

  const nextBtnClick = useCallback(async () => {
    await window.cpp_setNextStage();
    await getGameState();
  }, []);

  const stageProgress = useCallback(
    async (stageName: StageName) => {
      await window.cpp_stageProgress(stageName);
      await getGameState();
    },
    [getGameState]
  );

  return {
    gameState,
    setFieldState,
    updateFieldState,
    stageProgress,
    nextBtnClick,
  };
}
