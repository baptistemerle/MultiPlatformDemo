#include "ble_connection.h"

#include <QLowEnergyController>

BLEConnection::BLEConnection(const QBluetoothUuid& serviceUUID,
                             const QBluetoothUuid& configurationUUID,
                             QObject* parent)
  : QObject(parent)
  , m_serviceUuid(serviceUUID)
  , m_configurationUuid(configurationUUID)
{
}

void BLEConnection::connectToDevice(const QBluetoothDeviceInfo& deviceInfo)
{
  disconnectFromDevice();

  m_controller = QLowEnergyController::createCentral(deviceInfo, this);

  connect(m_controller, &QLowEnergyController::connected,
          this,         [this]()
  {
    m_controller->discoverServices();
    emit connected();
  });
  connect(m_controller, &QLowEnergyController::disconnected, this, &BLEConnection::disconnected);

  connect(m_controller, &QLowEnergyController::errorOccurred,
          this,         [this](QLowEnergyController::Error error)
  {
    QString errorMsg = "BLE error code: " + QString::number(error);
    emit errorOccurred(errorMsg);
  });

  connect(m_controller, &QLowEnergyController::serviceDiscovered,
          this,         [this](const QBluetoothUuid& newService)
  {
    if (newService == m_serviceUuid)
    {
       m_service = m_controller->createServiceObject(newService, this);

      connect(m_service, &QLowEnergyService::stateChanged,
              this, [this](QLowEnergyService::ServiceState state)
      {
        if (state == QLowEnergyService::RemoteServiceDiscovered)
        {
          m_configurationCharacteristic = m_service->characteristic(m_configurationUuid);

          if (m_configurationCharacteristic.isValid())
          {
            emit deviceReady();
          }
          else
          {
            emit errorOccurred("Configuration characteristic not found");
          }
        }
      });

      m_service->discoverDetails();
    }
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

void BLEConnection::sendConfiguration(const QByteArray& data)
{
  if (m_service && m_configurationCharacteristic.isValid())
  {
    m_service->writeCharacteristic(m_configurationCharacteristic, data, QLowEnergyService::WriteWithResponse);
  }
}
