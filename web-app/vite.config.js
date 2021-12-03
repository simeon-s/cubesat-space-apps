import { defineConfig } from "vite";
import { nodeResolve } from "@rollup/plugin-node-resolve";

// https://vitejs.dev/config/
export default defineConfig({
  build: {
    lib: {
      entry: "src/app.js",
      formats: ["es"],
    },
    rollupOptions: {
      // external: /^lit/,
      input: "index.html",
      plugins: [nodeResolve()],
    },
  },
});
