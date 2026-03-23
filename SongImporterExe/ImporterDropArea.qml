import QtQuick

Rectangle {
    id: root
    anchors.fill: parent
    color: "white"
    opacity: 0

    Behavior on opacity {
        NumberAnimation {
            duration: 200
            easing.type: Easing.InOutQuad
        }
    }

    Image {
        source: "qrc:/icons/file-icon.svg"
        anchors.centerIn: parent
        width: 100
        height:100

    }

    DropArea {
        anchors.fill: parent

        onEntered: {
            root.opacity = 0.5
        }
        onExited: {
            root.opacity = 0
        }
        onDropped:{
            root.opacity = 0
        }
    }
}
