import QtQuick 2.1
import "utils.js" as Utils

Rectangle {
    width: 200
    height: 200
    smooth: true
    property real h
    property real s : 1
    property real v : 1
    property color color1 /*: Utils.hsvToHsl(0.6,1.0,1.0)*/
    //visible: true
    property real ringWidth: 0.60

    onColorChanged: setColor()
    color : "transparent"
    signal changeColor(color color1);
    signal mouseRelease();
    function setColor(r,g,b) {
            var hsvColor = Utils.rgbToHsv(r,g,b)
            h = hsvColor.h
            color1.r = r/255;color1.g = g/255; color1.b = b/255;
            //s = hsvColor.s
           // v = hsvColor.v
    }

    // Color ring
    Item {
        id: outerCircle
        anchors.fill: parent
        smooth : true
        //antialiasing: true
        Image {
            id: bground
            anchors.fill: parent
            source: "qrc:/images/colorpickerImage.png"
            sourceSize: Qt.size(parent.width, parent.height)
            smooth: true
            visible: true
        }

        // Hue picker - kim quet vong tron
        Rectangle {
            id: pickerHue
            property int sizePickerHue: 3

            x: parent.width / 2
            y: (parent.height - sizePickerHue) / 2
            //width: parent.width/2
            width: parent.width/2-6
            height: sizePickerHue
            color: "white"
            antialiasing: true
            transform: Rotation {
                id: pickerHueAngle
                origin.x: 0
                origin.y: pickerHue.height / 2
                angle: (1 - h) * 360
            }
        }

        MouseArea {
            anchors.fill: parent
            function handleMouseHue(mouse) {
                if (mouse.buttons & Qt.LeftButton) {
                    var radianAngle = Math.atan2(outerCircle.height / 2 - mouse.y, mouse.x - outerCircle.width / 2)
                    var degreeAngle = (1 - radianAngle * 0.5 / Math.PI)
                    h = degreeAngle < 1 ? 1 - degreeAngle : 2 - degreeAngle
                    color1 = Utils.hsvToHsl(h, s, v, 1)
                    changeColor(color1)
                }
            }
            onPositionChanged: handleMouseHue(mouse)
            onPressed: handleMouseHue(mouse)
            onReleased: mouseRelease()
        }


        // Clearing inner circle
        Rectangle {
            id: innerCircle
            width: outerCircle.width * ringWidth
            height: outerCircle.height * ringWidth
            anchors.centerIn: parent
            radius: outerCircle.width * ringWidth / 2
            antialiasing: true
            //color: "#eeeeee"
            color : "grey"
        }

        // Color square - khung vuong ben trong
        Item {
            id: squareSV
            width: outerCircle.width * ringWidth / Math.sqrt(2)
            height: outerCircle.width * ringWidth / Math.sqrt(2)
            anchors.centerIn: parent

            Rectangle {
                anchors.fill: parent;
                rotation: -90
                gradient: Gradient {
                    GradientStop {position: 0.0; color: "white"}
                    GradientStop {position: 1.0; color: Qt.hsla(h, 1, 0.5, 1)}
                }
            }
            Rectangle {
                anchors.fill: parent
                gradient: Gradient {
                    GradientStop {position: 1.0; color: "#FF000000"}
                    GradientStop {position: 0.0; color: "#00000000"}
                }
            }

            // Saturation/Value picker - dau cham ben trong
            Item {
                id: pickerSV
                x: s * parent.width
                y: (1 - v) * parent.height
                property int radiusPickerSV: 5

                Rectangle {
                    x: -parent.radiusPickerSV
                    y: -parent.radiusPickerSV
                    width: parent.radiusPickerSV * 5
                    height: parent.radiusPickerSV * 5
                    radius: parent.radiusPickerSV*5
                    border.color: (pickerSV.x > squareSV.width / 2) || (pickerSV.y > squareSV.height / 2) ? "white" : "black"
                    border.width: 2
                    color: "transparent"
                    antialiasing: true
                }
            }

            MouseArea {
                anchors.fill: parent
                function handleMouseSV(mouse) {
                    if (mouse.buttons & Qt.LeftButton) {
                        s = Math.max(0, Math.min(width, mouse.x)) / parent.width
                        v = 1 - Math.max(0, Math.min(height, mouse.y)) / parent.height
                        color1 = Utils.hsvToHsl(h, s, v, 1)
                        changeColor(color1)
                    }
                }
                onPositionChanged: handleMouseSV(mouse)
                onPressed: handleMouseSV(mouse)
                onReleased: mouseRelease()
            }
        }
    }
}

