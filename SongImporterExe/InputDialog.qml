import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root

    property string headerText: "header"
    property string valueText:"value"
    property string buttonText:"Button"
    property double minWidth: 250
    property double actualWidth: parent.width === null ? minWidth : Math.max(parent.width,minWidth)

    signal buttonClicked()
    signal inputTextChanged(string text)
    implicitWidth:layout.implicitWidth
    implicitHeight: layout.implicitHeight
    width: actualWidth

    function setError(msg) {
     errorText.text = msg;
    }

    function clearError() {
     errorText.text = "";
    }

    GridLayout {
        id: layout
        columns: 2
        rows: 4
        rowSpacing: 2
        columnSpacing: 10
        anchors.fill: parent
        anchors.centerIn: parent

        Text {
            text: headerText
            font.pointSize: 8
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            Layout.row: 0
            Layout.column: 0
        }

        TextField{
            id:inputTextField
            text: valueText
            Layout.column: 0
            Layout.row:1
            font.pointSize: 10
            cursorVisible: false
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.NoWrap
            clip: true
            padding: 4
            color: "#141613"
            Layout.fillWidth: true
            Layout.minimumWidth: actualWidth - directoryButton.width - layout.columnSpacing
            onTextEdited:{
                valueText = text
                inputTextChanged(text);
            }

            background: Rectangle {
                id:rectangle
                border.color: "#141613"
                border.width: 1.5
                radius: 3
                color: "transparent"
            }
            onActiveFocusChanged: {
                var color = "#141613";
                if(activeFocus)
                {
                    var transparentColor=color + "33";
                    rectangle.color = transparentColor; //transparent
                }
                else
                {
                    rectangle.color = "transparent"
                }
            }
        }
        Rectangle {
                height: errorText.implicitHeight
                color: "transparent"
                Layout.column: 0
                Layout.row: 2
                Layout.columnSpan: 2
                Layout.fillWidth: true

                Text {
                    id: errorText
                    anchors.fill: parent
                    anchors.margins: 3
                    text: ""
                    color: "red"
                    font.pointSize: 8
                    wrapMode: Text.WordWrap
                }
            }

        Button {
            id: directoryButton
            height: 30
            Layout.column: 1
            Layout.row: 1
            onClicked: buttonClicked()

            background: Rectangle {
                implicitWidth: fileDirectoryText.implicitWidth + 8
                implicitHeight: fileDirectoryText.implicitHeight + 8
                border.width: 1.5
                radius: 3
                color: "#141613"

                Text {
                    id: fileDirectoryText
                    anchors.fill: parent
                    text: buttonText
                    font.pointSize: 8
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    color: "#CECCCC"
                    font.bold: true
                }
            }
        }
    }
}
