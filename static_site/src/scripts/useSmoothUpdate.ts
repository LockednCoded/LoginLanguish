import { useCallback, useEffect, useState } from "react";

export default function useSmoothUpdate(
  value: string,
  asyncUpdate: (e: React.ChangeEvent<HTMLInputElement>) => void
) {
  const [isFieldActive, setIsFieldActive] = useState(false);
  const [stableValue, setStableValue] = useState(value);

  const updateValue = useCallback((e: React.ChangeEvent<HTMLInputElement>) => {
    setStableValue(e.target.value);
    asyncUpdate(e);
  }, []);

  useEffect(() => {
    if (isFieldActive) return;
    setStableValue(value);
  }, [value, isFieldActive]);

  return [stableValue, updateValue, setIsFieldActive] as [
    string,
    (e: React.ChangeEvent<HTMLInputElement>) => void,
    React.Dispatch<React.SetStateAction<boolean>>
  ];
}
