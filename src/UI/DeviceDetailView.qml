import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
  property string selectedDeviceName: "Unknown"
  signal backPressed()

  ColumnLayout {
    anchors.centerIn: parent
    spacing: 20

    Label {
      text: "Connect to : " + selectedDeviceName
      font.pixelSize: 20
      Layout.alignment: Qt.AlignHCenter
    }

    Button {
      text: "Back"
      Layout.alignment: Qt.AlignHCenter
      onClicked: backPressed()
    }
  }
}