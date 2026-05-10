#include "ble_device_controller.h"

#include "ble_connection.h"
#include "ble_device_model.h"

#include "Core/dashboard_protocol.h"

BLEDeviceController::BLEDeviceController(BLEConnection* connection, BLEDeviceModel* model, QObject* parent)
  : QObject(parent)
  , m_connection(connection)
  , m_model(model)
{
  connect(m_connection, &BLEConnection::connected,
          this,         [this]()
  {
    setStatusMessage("Discovering services");
  });

  connect(m_connection, &BLEConnection::deviceReady,
          this,         [this]()
  {
    setIsReady(true);
    setStatusMessage("Device ready");
  });

  connect(m_connection, &BLEConnection::disconnected,
          this,         [this]()
  {
    setIsReady(false);
    setStatusMessage("Disconnected");
  });
}

bool BLEDeviceController::isReady() const
{
  return m_isReady;
}

QString BLEDeviceController::statusMessage() const
{
  return m_statusMessage;
}

void BLEDeviceController::connectToDevice(int index)
{
  QBluetoothDeviceInfo device = m_model->getDevice(index);

  if (device.isValid())
  {
    setIsReady(false);
    setStatusMessage("Connecting");

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

void BLEDeviceController::setIsReady(bool status)
{
  if (m_isReady != status)
  {
    m_isReady = status;
    emit isReadyChanged();
  }
}

void BLEDeviceController::setStatusMessage(const QString& msg)
{
  if (m_statusMessage != msg)
  {
    m_statusMessage = msg;
    emit statusMessageChanged();
  }
}