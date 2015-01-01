import QtQuick 2.0

Rectangle {
    id: rectangle1
    width: 100
    height: 62
    color: "#7b87c1"
    radius: 0
    border.color: "#00000000"
    antialiasing: true

    Text {
        id: text1
        text: qsTr("Button")
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        scale: 1
        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 16
    }
}
