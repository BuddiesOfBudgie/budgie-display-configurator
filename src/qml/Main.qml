import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import org.kde.kirigami as Kirigami
import org.buddiesofbudgie.DisplayConfig

Kirigami.ApplicationWindow {
    id: root

    width: 400
    height: 300

    title: i18nc("@title:window", "Displays")

    pageStack.initialPage: Kirigami.Page {
        ColumnLayout {
            id: rootLayout

            Outputs {}
        }
    }
}
