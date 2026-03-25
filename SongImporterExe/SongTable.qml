import QtQuick
import QtQuick.Layouts

Rectangle {

    Component {
        id: contactDelegate
        Item {
            id: myItem
            required property string title
            required property string artists
            required property string album
            required property url albumCover
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
                    text: "<b>Title:</b><br /> " + title
                    Layout.fillWidth: true
                    Layout.preferredWidth: 7
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    elide: Text.ElideRight
                    wrapMode: Text.NoWrap
                    clip: true
                }

                Text {
                    text: "<b>Album:</b><br /> " + album
                    Layout.fillWidth: true
                    Layout.preferredWidth: 7
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    elide: Text.ElideRight
                    wrapMode: Text.NoWrap
                    clip: true
                }
                Text {
                    text: "<b>Artists:</b><br /> " + artists
                    Layout.fillWidth: true
                    Layout.preferredWidth: 7
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    elide: Text.ElideRight
                    wrapMode: Text.NoWrap
                    clip: true
                }
                Text {
                    text: "<b>Year:</b><br /> " + year
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

    ListView {
        anchors.fill: parent
        model: ContactModel {}
        delegate: contactDelegate
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        clip:true
    }
}
