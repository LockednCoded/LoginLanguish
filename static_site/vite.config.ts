import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";
import Icons from "unplugin-icons/vite";

export default defineConfig({
  root: "src",
  build: {
    outDir: "../dist",
    target: "es2015",
    minify: false,
  },
  plugins: [
    react(),
    Icons({
      autoInstall: true,
      compiler: "jsx",
      jsx: "react",
    }),
  ],
});
