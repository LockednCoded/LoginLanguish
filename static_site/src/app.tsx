import React from "react";
import { createRoot } from "react-dom/client";
import LoginPage from "./components/LoginPage";
import "./styles/main.css";

const reactRoot = document.getElementById("react-root");

const App = () => {
  return (
    <div className="h-screen bg-gray-700 flex justify-center items-center overflow-hidden">
      <LoginPage />
    </div>
  );
};

if (reactRoot) {
  createRoot(reactRoot).render(<App />);
}
