import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
  signal deviceSelected(int deviceIndex, string deviceName)

  ColumnLayout {
    anchors.fill: parent
    anchors.margins: 10
    spacing: 10

    Button {
      Layout.fillWidth: true
      text: discoveryController.isScanning ? "Stop scan" : "Start scan"

      onClicked: {
        if (discoveryController.isScanning)
        {
          discoveryController.stopScan()
        }
        else
        {
          discoveryController.startScan()
        }
      }
    }

    ListView {
      Layout.fillWidth: true
      Layout.fillHeight: true
      model: bleModel
      clip: true

      delegate: ItemDelegate {
        width: ListView.view.width

        text: deviceName + "\n" + deviceAddress

        onClicked: {
          deviceSelected(index, deviceName)
        }
      }
    }
  }
}