#include "ble_connection.h"

#include <QLowEnergyController>

BLEConnection::BLEConnection(QObject* parent)
  : QObject(parent)
{
}

void BLEConnection::connectToDevice(const QBluetoothDeviceInfo& deviceInfo)
{
  disconnectFromDevice();

  m_controller = QLowEnergyController::createCentral(deviceInfo, this);

  connect(m_controller, &QLowEnergyController::connected,    this, &BLEConnection::connected);
  connect(m_controller, &QLowEnergyController::disconnected, this, &BLEConnection::disconnected);

  connect(m_controller, &QLowEnergyController::errorOccurred,
          this,         [this](QLowEnergyController::Error error)
          {
            QString errorMsg = "BLE error code: " + QString::number(error);
            emit errorOccurred(errorMsg);
          });

  m_controller->connectToDevice();
}

void BLEConnection::disconnectFromDevice()
{
  if (m_controller)
  {
    m_controller->disconnectFromDevice();
    m_controller->deleteLater();
    m_controller = nullptr;
  }
}
