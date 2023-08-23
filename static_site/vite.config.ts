import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";
import Icons from "unplugin-icons/vite";

export default defineConfig({
  root: "src",
  plugins: [
    react(),
    Icons({
      autoInstall: true,
      compiler: "jsx",
      jsx: "react",
    }),
  ],
});
