import QtQuick
import QtQuick.Controls

Window {
  width: 400
  height: 600
  visible: true
  title: "Multi Platform BLE"

  StackView {
    id: stackView
    anchors.fill: parent
    initialItem: deviceListPage
  }

  Component {
    id: deviceListPage

    DeviceListView {
      onDeviceSelected: (index, name) => {
        bleController.stopScan()
        bleController.connectToDevice(index)
        stackView.push(deviceDetailPage, { "selectedDeviceName": name })
      }
    }
  }

  Component {
    id: deviceDetailPage

    DeviceDetailView {
      onBackPressed: {
        bleController.disconnectFromDevice()
        stackView.pop()
      }
    }
  }
}