import QtQuick
import QtQuick.Layouts
import SongImporter.SongListModel

Rectangle {

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
    }

    ListView {
        anchors.fill: parent
        model: SongListModel
        delegate: contactDelegate
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        clip:true
    }
}
