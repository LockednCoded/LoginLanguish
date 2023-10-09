import React, { useEffect, useState } from "react";
import WarningIcon from "~icons/pajamas/warning-solid";
import { GameState, SetFieldStateFunc } from "../scripts/useBindings";

function DwayneActionButton({
  displayText,
  onClick,
  disabled,
  onMouseEnter,
  onMouseLeave,
}: {
  displayText: string;
  onClick: () => void;
  disabled?: boolean;
  onMouseEnter?: () => void;
  onMouseLeave?: () => void;
}) {
  return (
    <button
      className="px-1 group"
      onMouseEnter={disabled ? null : onMouseEnter}
      onMouseLeave={disabled ? null : onMouseLeave}
      type="button"
      onClick={disabled ? null : onClick}
      disabled={disabled}
    >
      <div
        className={`px-3 py-1.5 text-sm font-bold border-neutral-800 border rounded-md ${
          disabled ? "opacity-75" : "group-hover:bg-neutral-400"
        }`}
      >
        {displayText}
      </div>
    </button>
  );
}

export default function Dwayne({
  dwayneState,
  updateFieldState,
  nextBtnClick,
}: {
  dwayneState: GameState["stages"][5]["state"];
  updateFieldState: SetFieldStateFunc;
  nextBtnClick: () => Promise<void>;
}) {
  const [cooldownFace, setCooldownFace] = useState(null as string);
  const [timeoutN, setTimeoutN] = useState(
    null as ReturnType<typeof setTimeout>
  );
  const [prevIteration, setPrevIteration] = useState(0);
  useEffect(() => {
    if (dwayneState.iteration !== prevIteration) {
      setPrevIteration(dwayneState.iteration);
      setCooldownFace(dwayneState.tempData.face);
      new Audio(dwayneState.tempData.sound).play();
      clearTimeout(timeoutN);
      setTimeoutN(
        setTimeout(() => {
          setCooldownFace(null);
        }, dwayneState.tempData.timeout)
      );
    }
  }, [
    dwayneState.iteration,
    dwayneState.tempData,
    timeoutN,
    setCooldownFace,
    setTimeoutN,
  ]);

  return (
    <div className="bg-gray-950/25 fixed z-10 h-full w-full top-0 left-0 flex items-center justify-center">
      <div className="bg-white w-[590px] h-[320px] rounded-md flex flex-col">
        <div className="flex items-center px-4 py-3 bg-red-600">
          <div className="text-2xl">
            <WarningIcon className="w-6 h-6 mr-3 ml-1 text-white" />
          </div>
          <div className="flex justify-between font-bold text-white w-full text-lg">
            <p>You must defeat DWAYNE to proceed.</p>
            <p>Round {dwayneState.round}/3</p>
          </div>
        </div>
        <div className="flex p-5 grow overflow-hidden">
          <div className="h-full">
            <img
              className="w-[200px] h-full object-cover"
              src={
                cooldownFace != null && !dwayneState.gameOver
                  ? cooldownFace
                  : dwayneState.face
              }
            />
          </div>
          <div className="flex flex-col justify-between grow px-4">
            <div className="flex flex-col justify-between grow pb-4">
              <p className="text-center text-lg">{dwayneState.topText}</p>
              <p className="text-center text-lg font-bold">
                {dwayneState.bottomText}
              </p>
            </div>
            <div className="flex justify-center">
              {dwayneState.gameOver ? (
                dwayneState.gameWon ? (
                  <DwayneActionButton
                    disabled={cooldownFace != null}
                    displayText="Continue"
                    onClick={nextBtnClick}
                  />
                ) : (
                  <DwayneActionButton
                    disabled={cooldownFace != null}
                    displayText="🔄 Rematch"
                    onClick={() =>
                      updateFieldState("dwayne", "action", "rematch")
                    }
                  />
                )
              ) : (
                [
                  ["📄 Paper", "paper", 1],
                  ["✂️ Scissors", "scissors", 2],
                  ["🪨 Rock", "rock", 3],
                ].map(([displayName, vName, id]: [string, string, number]) => (
                  <DwayneActionButton
                    displayText={displayName}
                    disabled={cooldownFace != null}
                    onClick={() => updateFieldState("dwayne", "action", vName)}
                    onMouseEnter={() =>
                      updateFieldState("dwayne", "hover", id.toString())
                    }
                    onMouseLeave={() =>
                      updateFieldState("dwayne", "hover", "0")
                    }
                  />
                ))
              )}
            </div>
          </div>
        </div>
      </div>
    </div>
  );
}
