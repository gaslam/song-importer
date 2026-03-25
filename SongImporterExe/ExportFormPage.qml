import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import SongImporter.Utils
import SongImporter.FileReceiver
import QtQuick.Dialogs

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
                Layout.fillWidth: true
                Layout.fillHeight: true
                ImporterDropArea{
                onDropped: function(drop) {
                    for(const fileurl of drop.urls)
                    {
                       let song = fileReceiver.getSongFromFile(fileurl)
                        console.log(song.title)
                    }
                }
                }
            }

        }

        MessageDialog{
            id:errorDialog
            text: "A song was detected"

        }

        FileReceiver {
            id:fileReceiver

        }


    }
}
