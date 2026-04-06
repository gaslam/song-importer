import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import SongImporter.Utils
import QtQuick.Dialogs
import SongImporter.SongListModel

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
                    Layout.fillWidth: true
                    inputText: FileUtils.softwareDataLocation(FileUtils.Rekordbox)
                }
                FolderInput{
                    id:folderInput
                    Layout.fillWidth: true
                    minWidth: 200
                    inputText: FileUtils.musicFolder()
                }
            }
            SongTable{
                id:songTable
                Layout.fillWidth: true
                Layout.fillHeight: true
                ImporterDropArea{
                    onDropped: function(drop) {
                        songTable.addSongsFromFileToList(drop.urls)
                    }
                }
            }

            Connections {
                target: SongListModel

                function onErrorReceived(error) {
                    addError(error);
                }

                property var errors: []

                function addError(error) {
                    let dialog = errorDialogComponent.createObject(root, { errorMessage: error });
                    if (dialog) dialog.open();
                }

            }

        }

        Component {
            id: errorDialogComponent

            MessageDialog {
                property string errorMessage: ""
                text: "An error has occurred"
                informativeText: errorMessage
                buttons: MessageDialog.Ok

                onAccepted: destroy()
                onRejected: destroy()
            }
        }

    }
}
