import QtQuick

Window {
  width: 640
  height: 480
  visible: true
  title: qsTr("Hello World")

  Rectangle {
    width: 200
    height: 200
    anchors.centerIn: parent
    color: "lightblue"

    Text {
      id: name
      text: qsTr("Hello")
      anchors.centerIn: parent
    }
  }
}
