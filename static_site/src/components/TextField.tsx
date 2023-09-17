import React from "react";
import useSmoothUpdate from "../scripts/useSmoothUpdate";

export default function TextField(props: {
  type: "text" | "password" | "date";
  name: string;
  value: string;
  onChange: (val: string) => void;
  disabled?: boolean;
  className?: string;
}) {
  const [stableValue, updateValue, setFieldIsActive] = useSmoothUpdate(
    props.value,
    props.onChange
  );

  return (
    <div className={props.className}>
      <div>
        <label
          className="text-sm text-gray-800 font-light mb-0.5 block"
          htmlFor={props.name}
        >
          {props.name}
        </label>
        <input
          className={`border rounded border-black w-full h-9 p-2 box-border outline-none disabled:opacity-75 select-text ${
            props.type == "password"
              ? "[-webkit-text-security:disc] tracking-wider"
              : ""
          }`}
          data-test-id={`text-field-${props.name}`}
          type={{ password: "text", text: "text", date: "date" }[props.type]}
          name={props.name}
          id={props.name}
          onBlur={() => setFieldIsActive(false)}
          onFocus={() => setFieldIsActive(true)}
          autoComplete="off"
          value={stableValue}
          onChange={updateValue}
          disabled={props.disabled || false}
        />
      </div>
    </div>
  );
}
