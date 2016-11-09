.pragma library

var Style = {}

Style.TextAppearance = {
  textSize : 16
}

var icon_mapping = {}
var UIIconSet = "flaticon";

function lookupIconName(icon) {
    if (icon_mapping[UIIconSet + "-" + icon] === undefined) {
        console.log("Icon not found: [" + icon + "]")
    }

    return icon_mapping[UIIconSet + "-" + icon];
}
