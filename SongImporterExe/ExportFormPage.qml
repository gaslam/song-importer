import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    Rectangle {
        anchors.fill: parent
        color: "white"
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 10

            RowLayout {
                id:rowLayout
                Layout.fillWidth: true
                Layout.preferredHeight: fileInput.height
                spacing: 10
                FileInput {
                    id:fileInput
                    minWidth: 200
                    Layout.fillWidth: true }
                FolderInput{
                    id:folderInput
                    Layout.fillWidth: true
                    minWidth: 200
                }
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true   // takes remaining space
                color: "lightgreen"
                Text { anchors.centerIn: parent; text: "80% Row"  }
            }
        }
    }
}
