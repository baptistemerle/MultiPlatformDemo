#include "ble_device_controller.h"

#include "ble_connection.h"
#include "ble_device_model.h"

#include "Core/dashboard_protocol.h"

BLEDeviceController::BLEDeviceController(BLEConnection* connection, BLEDeviceModel* model, QObject* parent)
  : QObject(parent)
  , m_connection(connection)
  , m_model(model)
{
}

void BLEDeviceController::connectToDevice(int index)
{
  QBluetoothDeviceInfo device = m_model->getDevice(index);

  if (device.isValid())
  {
    m_connection->connectToDevice(device);
  }
}

void BLEDeviceController::disconnectFromDevice()
{
  m_connection->disconnectFromDevice();
}

void BLEDeviceController::sendLimit(int value)
{
  QByteArray payload = DashboardProtocol::encodeLimitMessage(value);

  m_connection->sendConfiguration(payload);
}