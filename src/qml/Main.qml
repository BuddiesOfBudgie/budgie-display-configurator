import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import org.kde.kirigami as Kirigami

Kirigami.ApplicationWindow {
    id: root

    width: 400
    height: 300

    title: i18nc("@title:window", "Displays")

    pageStack.initialPage: Kirigami.Page {
        Controls.Label {
            anchors.centerIn: parent
            text: Backend.test
        }
    }
}
