import QtQuick

Rectangle {
    id: root
    anchors.fill: parent
    color: "white"
    opacity: 0

    signal dropped(DragEvent drop )

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
        onDropped: function(drop) {
            root.opacity = 0
            root.dropped(drop)
        }
    }
}
