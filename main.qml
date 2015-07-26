import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0

ApplicationWindow {
    width: 640
    height: 480
    title: ""
    visible: true

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: messageDialog.show(qsTr("Open url"));
            }
            MenuItem {
                text: qsTr("E&xit")
                onTriggered: Qt.quit();
            }
        }
    }

    MainForm {
    }

    statusBar: StatusBar {
        RowLayout {
            anchors.fill: parent
            Label { text: "Open url" }
    }
    }   
MessageDialog {
        id: messageDialog
        title: qsTr("Type url?")

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }

}
