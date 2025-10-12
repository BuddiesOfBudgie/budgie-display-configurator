import QtQuick
import QtQuick.Layouts

Rectangle {
    Repeater {
        model: Backend.outputs
        Rectangle {
            required property string serial
            required property string name
            required property rect geometry

            implicitHeight: geometry.height * 0.1
            implicitWidth: geometry.width * 0.1
            x: geometry.x * 0.1
            y: geometry.y * 0.1

            Text {
                text: "Name: " + name + " (" + serial + ")"
            }
        }
    }
}