const { InitTess, SetImage, GetUTF8Text, DestroyTess } = require("./build/Release/tess.node")

InitTess("eng")
SetImage("./WX20220610-160540@2x.png")
console.log(GetUTF8Text())
DestroyTess()
