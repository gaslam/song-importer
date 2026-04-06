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
                    errorDialog.addError(error);
                }
            }

        }

        MessageDialog{
            id:errorDialog
            text: "A error has occured"
            property var errors: []

            function addError(error)
            {
                errors.push(error);
                if(!errorDialog.visible)
                {
                    openDialogIfErrorsNotEmpty();
                }
            }

            function openDialogIfErrorsNotEmpty()
            {
                if(errors.length > 0)
                {
                    let currError= errors[0];
                    errorDialog.informativeText = currError;
                    errorDialog.open();
                    errors.pop();
                }
            }

            onAccepted: {
                openDialogIfErrorsNotEmpty();
            }

        }


    }
}
