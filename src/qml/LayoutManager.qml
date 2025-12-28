// SPDX-FileCopyrightText: Budgie Desktop Developers
// SPDX-License-Identifier: MPL-2.0

import QtQuick
import QtQuick.Layouts
import org.kde.kirigami as Kirigami

Rectangle {
    Kirigami.Theme.colorSet: Kirigami.Theme.Window
    color: Kirigami.Theme.alternateBackgroundColor
    width: (Backend.layout.globalRect.width * 0.10) + (Kirigami.Units.largeSpacing * 2)
    height: (Backend.layout.globalRect.height * 0.10) + (Kirigami.Units.largeSpacing * 2)
    radius: Kirigami.Units.cornerRadius

    Component {
        id: outputDelegate

        Item {
            id: delegateItem
            required property string serial
            required property string name
            required property rect geometry

            height: geometry.height * 0.10
            width: geometry.width * 0.10

            Rectangle {
                id: serial
                Kirigami.Theme.colorSet: Kirigami.Theme.Selection
                color: Kirigami.Theme.disabledTextColor
                radius: Kirigami.Units.cornerRadius

                height: delegateItem.geometry.height * 0.10
                width: delegateItem.geometry.width * 0.10
                x: delegateItem.geometry.x * 0.10
                y: delegateItem.geometry.y * 0.10

                ColumnLayout {
                    anchors.fill: parent
                    Kirigami.Heading {
                        Layout.fillWidth: true
                        horizontalAlignment: Text.AlignHCenter

                        level: 1

                        Kirigami.Theme.inherit: true
                        color: Kirigami.Theme.textColor

                        text: delegateItem.name + " (" + delegateItem.serial + ")"
                    }
                    Kirigami.Heading {
                        Layout.fillWidth: true
                        horizontalAlignment: Text.AlignHCenter
                        text: delegateItem.geometry.width + "x" + delegateItem.geometry.height
                    }
                }
            }
        }
    }

    GridView {
        id: grid
        cellWidth: 100
        cellHeight: 100
        anchors.fill: parent
        anchors.margins: Kirigami.Units.largeSpacing
        width: parent.width
        height: parent.height

        model: Backend.layout.model
        delegate: outputDelegate

        highlight: Rectangle {
            Kirigami.Theme.colorSet: Kirigami.Theme.Selection
            Kirigami.Theme.inherit: false
            color: Kirigami.Theme.highlightColor
            radius: Kirigami.Units.cornerRadius
        }
    }
}
