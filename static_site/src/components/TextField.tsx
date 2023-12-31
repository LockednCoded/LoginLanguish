import React, { useState } from "react";
import useSmoothUpdate from "../scripts/useSmoothUpdate";
import { Icon } from "@iconify/react";

export default function TextField(props: {
  type: "text" | "password" | "date";
  name: string;
  value: string;
  onChange: (_val: string) => void;
  onEnter?: () => void;
  disabled?: boolean;
  className?: string;
}) {
  const [stableValue, updateValue, setFieldIsActive] = useSmoothUpdate(
    props.value,
    props.onChange
  );

  const [showPassword, setShowPassword] = useState(false);

  return (
    <div className={props.className}>
      <div>
        <label
          className="text-sm text-gray-800 font-light mb-0.5 block"
          htmlFor={props.name}
        >
          {props.name}
        </label>
        <div className="w-full relative">
          <input
            className={`border rounded border-black w-full h-9 p-2 box-border outline-none disabled:opacity-75 select-text${
              props.type == "password"
                ? ` font-mono${
                    !showPassword ? " [-webkit-text-security:disc]" : ""
                  }`
                : ""
            }`}
            data-test-id={`text-field-${props.name}`}
            type={{ password: "text", text: "text", date: "date" }[props.type]}
            name={props.name}
            id={props.name}
            onBlur={() => setFieldIsActive(false)}
            onFocus={() => {
              setFieldIsActive(true);
              setShowPassword(false);
            }}
            autoComplete="off"
            onKeyDown={(e) => {
              if (e.key == "Enter" && props.onEnter) props.onEnter();
            }}
            autoCorrect="off"
            autoCapitalize="off"
            spellCheck="false"
            value={stableValue}
            onChange={(e) => {
              if (showPassword) setShowPassword(false);
              updateValue(e.target.value);
            }}
            disabled={props.disabled || false}
          />
          {props.type == "password" && (
            <div
              className="absolute top-1/2 -translate-y-1/2 right-2 text-lg cursor-pointer"
              data-test-id={`text-field-${props.name}-show-password`}
              onClick={() => setShowPassword(!showPassword)}
            >
              {showPassword ? (
                <Icon icon="tabler:eye" />
              ) : (
                <Icon icon="tabler:eye-closed" />
              )}
            </div>
          )}
        </div>
      </div>
    </div>
  );
}
