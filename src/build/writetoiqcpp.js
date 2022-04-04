const fs = require("fs");
const path = require("path");
const buildDir = path.dirname(__filename) + "/../robot/"
const code = fs.readFileSync(buildDir + "./code.c++")
const toWriteTo = fs.readFileSync(buildDir + "Baller.iqcpp");
// replaced any newlines to \n
function nl2slashn(str){
    return str.toString().replace(/\n/g, "");
    //return str.toString().replace(/(?:\r\n|\r|\n)/g, '\\n');
}
(async () => {
    console.log("Parsing JSON");
    const parsedJson = JSON.parse(toWriteTo);
    // write to the "textContent" section
    parsedJson["textContent"] = nl2slashn(code);
    console.log(`Saving: \n${code}\n\nto Baller.iqcpp`)
    fs.writeFileSync(buildDir + "Baller.iqcpp", JSON.stringify(parsedJson))
})();
