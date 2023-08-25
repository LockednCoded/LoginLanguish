import React from "react";
import { useEffect, useState } from "react";
import WarningIcon from "~icons/pajamas/warning-solid";

export function ValidationBox(props: {
  message: string;
  className?: string;
  shown: boolean;
}) {
  const [persistedMessage, setPersistedMessage] = useState(props.message);
  useEffect(() => {
    if (props.message !== "") setPersistedMessage(props.message);
  }, [props.message]);

  return (
    <div
      className={`border-[2.5px] border-yellow-400 rounded-lg height-hidable ${
        props.shown ? "" : "height-hidden"
      } ${props.className}`}
    >
      <div className="flex items-center p-3">
        <WarningIcon className="w-6 h-6 mr-3 ml-1 text-yellow-400" />
        <p className="text-sm">{persistedMessage}</p>
      </div>
    </div>
  );
}
