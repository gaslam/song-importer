import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import SongImporter.SongListModel

Rectangle {
    color:"gray"
    Text{
        id:fileDropText
        anchors.centerIn: parent
        text: "Place your audio files here."
    }
    Component {
        id: contactDelegate
        Item {
            required property string title
            required property string artists
            required property url albumCover
            required property string album
            required property int year
            anchors.left: parent.left; anchors.right: parent.right
            Layout.fillWidth: true
            height: 50
            RowLayout {
                anchors.fill: parent
                spacing: 10

                Image{
                    source: albumCover

                    Layout.preferredWidth: 4
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    fillMode: Image.PreserveAspectFit
                    smooth: true

                }

                Text {
                    text: "<b>Title:</b><br /> " + (!title.length !== 0 ? title :"unknown")
                    Layout.fillWidth: true
                    Layout.preferredWidth: 7
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    elide: Text.ElideRight
                    wrapMode: Text.NoWrap
                    clip: true
                }

                Text {
                    text: "<b>Album:</b><br /> " + (!album.length !== 0 ? album : "unknown")
                    Layout.fillWidth: true
                    Layout.preferredWidth: 7
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    elide: Text.ElideRight
                    wrapMode: Text.NoWrap
                    clip: true
                }
                Text {
                    text: "<b>Artists:</b><br /> " + (!artists.length !== 0 ? artists : "unknown")
                    Layout.fillWidth: true
                    Layout.preferredWidth: 7
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    elide: Text.ElideRight
                    wrapMode: Text.NoWrap
                    clip: true
                }
                Text {
                    text: "<b>Year:</b><br /> " + (year > 0 ? year : "unknown")
                    Layout.fillWidth: true
                    Layout.preferredWidth: 7
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    elide: Text.ElideRight
                    wrapMode: Text.NoWrap
                    clip: true
                }
            }
        }
    }

    function addSongsFromFileToList(file)
    {
        SongListModel.extractSongsFromFile(file)
        fileDropText.visible = false
    }

    ListView {
        anchors.fill: parent
        model: SongListModel
        delegate: contactDelegate
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        clip:true
        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AsNeeded
        }
    }
}
