import React from "react";

export default function TextField(props: {
  type: "text" | "password" | "date";
  name: string;
  value: string;
  onChange: (e: React.ChangeEvent<HTMLInputElement>) => void;
  disabled?: boolean;
  className?: string;
}) {
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
          className={`border rounded border-black w-full h-9 p-2 box-border outline-none disabled:opacity-75 ${
            props.type == "password"
              ? "[-webkit-text-security:disc] tracking-wider"
              : ""
          }`}
          type={{ password: "text", text: "text", date: "date" }[props.type]}
          name={props.name}
          id={props.name}
          autoComplete="off"
          value={props.value}
          onChange={props.onChange}
          disabled={props.disabled || false}
        />
      </div>
    </div>
  );
}
