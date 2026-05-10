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
        discoveryController.stopScan()
        deviceController.connectToDevice(index)
        stackView.push(deviceDetailPage, { "selectedDeviceName": name })
      }
    }
  }

  Component {
    id: deviceDetailPage

    DeviceDetailView {
      onBackPressed: {
        deviceController.disconnectFromDevice()
        stackView.pop()
      }
    }
  }
}