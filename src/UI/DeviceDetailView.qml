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

    Label {
      text: "Limit : " + limitSlider.value
      Layout.alignment: Qt.AlignHCenter
    }

    Slider {
      id: limitSlider
      from: 0
      to: 200
      stepSize: 1
      Layout.alignment: Qt.AlignHCenter
    }

    Button {
      text: "Send"
      Layout.alignment: Qt.AlignHCenter

      onClicked: {
        deviceController.sendLimit(limitSlider.value)
      }
    }

    Button {
      text: "Back"
      Layout.alignment: Qt.AlignHCenter
      onClicked: backPressed()
    }
  }
}