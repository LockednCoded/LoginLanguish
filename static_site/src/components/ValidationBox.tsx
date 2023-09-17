import React, { useEffect, useState } from "react";
import WarningIcon from "~icons/pajamas/warning-solid";

export function ValidationBox(props: {
  messages: string[];
  className?: string;
}) {
  return (
    <div>
      {[1, 1, 1, 1, 1].map((_, i) => {
        const hasMessage = props.messages.length > i;
        return (
          <div
            className={`border-[2.5px] border-yellow-400 rounded-lg height-hidable ${
              hasMessage ? "" : "height-hidden"
            } ${props.className}`}
          >
            <div className="flex items-center p-3">
              <div className="text-xl">
                <WarningIcon className="w-6 h-6 mr-3 ml-1 text-yellow-400" />
              </div>
              <p className="text-sm">{props.messages[i]}</p>
            </div>
          </div>
        );
      })}
    </div>
  );
}
