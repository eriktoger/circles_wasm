const express = require("express");
const app = express();
if (process.env.USEC === "true") {
  app.use(express.static("public/C"));
} else {
  app.use(express.static("public/CPP"));
}

app.listen(2222, () => console.log("Server running on 2222"));
