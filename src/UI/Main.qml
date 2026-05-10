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

  Popup {
    id: globalErrorPopup
    anchors.centerIn: parent
    width: parent.width * 0.8
    modal: true
    focus: true
    closePolicy: Popup.NoAutoClose
    padding: 20

    visible: alertController.errorMessage !== ""

    background: Rectangle {
      color: "white"
      border.color: "red"
      border.width: 2
      radius: 8
    }

    Column {
      width: parent.width
      spacing: 15

      Label {
        text: "Error occured"
        font.bold: true
        color: "red"
        font.pixelSize: 16
        anchors.horizontalCenter: parent.horizontalCenter
      }

      Label {
        text: alertController.errorMessage
        wrapMode: Text.Wrap
        width: parent.width
        horizontalAlignment: Text.AlignHCenter
      }

      Button {
        text: "Close"
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: alertController.clearError()
      }
    }
  }
}