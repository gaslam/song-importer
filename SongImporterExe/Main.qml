import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Song Importer")
    minimumWidth: 460
    minimumHeight: 345
    ExportFormPage{anchors.fill: parent}
}

