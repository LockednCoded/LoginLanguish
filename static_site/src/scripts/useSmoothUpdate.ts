import { useCallback, useEffect, useState } from "react";

export default function useSmoothUpdate(
  value: string,
  asyncUpdate: (val: string) => void
) {
  const [isFieldActive, setIsFieldActive] = useState(false);
  const [stableValue, setStableValue] = useState(value);

  const updateValue = useCallback((newVal: string) => {
    let cleanValue = newVal
      .replace(/[\u2014]/g, "--") // emdash
      .replace(/[\u2022]/g, "*") // bullet
      .replace(/[\u2018\u2019]/g, "'") // smart single quotes
      .replace(/[\u201C\u201D]/g, '"') // smart double quotes
      .replace(/[^ -~]/g, ""); // remove non-ASCII characters
    setStableValue(cleanValue);
    asyncUpdate(cleanValue);
  }, []);

  useEffect(() => {
    if (isFieldActive) return;
    setStableValue(value);
  }, [value, isFieldActive]);

  return [stableValue, updateValue, setIsFieldActive] as [
    string,
    (newVal: string) => void,
    React.Dispatch<React.SetStateAction<boolean>>
  ];
}
