import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "." as App

ApplicationWindow {
    id: window
    objectName: "window"
    title: qsTr("LLM-Chat")
    visible: true
    width: 1000
    height: 800
    opacity: settings.windowOpacity

    property int oldWindowVisibility: Window.Windowed

    function toggleFullScreen() {
        if (window.visibility === Window.FullScreen) {
            window.visibility = oldWindowVisibility
        }
        else {
            oldWindowVisibility = window.visibility
            window.visibility = Window.FullScreen
        }
    }

    menuBar: App.MenuBar {
    }

    App.ChatView {
    }
    // ColumnLayout {
    //     anchors.fill: parent
    //     anchors.margins: 10
        // ListView {
        //     Layout.fillHeight: true
        //     Layout.fillWidth: true
        //     clip: true
        //     model: chatBackend.model
        //     delegate: Rectangle {
        //         width: ListView.view.width
        //         height: messageText.implicitHeight + 20
        //         color: isUser ? "#e6e6e6" : "#f0f0f0"

        //         Text {
        //             id: messageText
        //             text: isUser ? "You: " + model.text : "AI: " + model.text
        //             wrapMode: Text.Wrap
        //             anchors.fill: parent
        //             anchors.margins: 10
        //         }
        //     }
        //     ScrollBar.vertical: ScrollBar{}
        // }
        // RowLayout {
        //     TextField {
        //         id : textFieldMessage
        //         placeholderText: qsTr("Your Message...")
        //         Layout.fillWidth: true
        //         onAccepted: buttonSend.clicked()
        //     }
        //     Button {
        //         id: buttonSend
        //         text: qsTr("Send")
        //         onClicked: {
        //             console.log("Send")
        //             chatBackend.sendMessage(textFieldMessage.text)
        //             textFieldMessage.clear()
        //         }
        //     }
        // }
    // }

    App.AboutDialog {
        id: aboutDialog
        anchors.centerIn: parent
        parent: Overlay.overlay
    }

    App.OptionsDialog {
        id: optionsDialog
        anchors.centerIn: parent
        parent: Overlay.overlay
    }
}
