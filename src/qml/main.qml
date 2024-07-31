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
