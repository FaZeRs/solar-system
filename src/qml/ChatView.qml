import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
    id: chatView
    anchors.fill: parent
    anchors.margins: 10

    ListView {
        id: chatList
        Layout.fillWidth: true
        Layout.fillHeight: true
        spacing: 8
        clip: true
        model: chatBackend.model
        delegate: Rectangle {
            width: ListView.view.width
            height: messageText.implicitHeight + 20
            // color: isUser ? "#e6e6e6" : "#f0f0f0"
            gradient: Gradient {
                orientation: Gradient.Horizontal
                GradientStop { position: -0.2; color: isUser ? "#252B35" : "#32CEF2" }
                GradientStop { position: 1.0; color: isUser ? "#3f4045" : "#2D6CF7" }
            }
            radius: 12

            Text {
                id: messageText
                text: model.text
                color: "#FFFFFF"
                wrapMode: Text.Wrap
                anchors.fill: parent
                anchors.margins: 10
                textFormat: Text.MarkdownText
            }
        }
        ScrollBar.vertical: ScrollBar{}
    }

    RowLayout {
        TextField {
            id: messageField
            placeholderText: qsTr("Type your message here...")
            Layout.fillWidth: true
            onAccepted: sendMessage()
        }

        Button {
            id: sendButton
            text: qsTr("Send")
            onClicked: sendMessage();
        }

        Shortcut {
            sequence: visible ? "Ctrl+Return" : ""
            onActivated: sendMessage();
        }
    }

    function sendMessage() {
        if(messageField.text == "") {
            return;
        }

        chatBackend.sendMessage(messageField.text);
        messageField.text = "";
    }
}