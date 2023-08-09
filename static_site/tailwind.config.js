/** @type {import('tailwindcss').Config} */

export default {
  content: ["./src/index.html", "./src/**/*.{js,ts,jsx,tsx}"],
  theme: {
    extend: {
      fontFamily: { sans: ["Arial", "sans-serif"] },
    },
  },
  plugins: [],
};
