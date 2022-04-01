const fs = require("fs");
const path = require("path");

const buildDir = path.dirname(__filename) + "/../robot/"
const iq = fs.readFileSync(buildDir + "DSHSMistake.iqcpp");
const where2build = path.dirname(__filename) + "/../../"

fs.writeFileSync(where2build + "main.cpp", JSON.stringify(JSON.parse(iq)["textContent"]))