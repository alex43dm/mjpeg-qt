import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Item {
    width: 640
    height: 480

    Grid {
        id: grid1
        columns: 1
        rows: 3

        Image {
            id: image1
            anchors.fill: parent
            source: "default.jpeg"
        }
    }

}
