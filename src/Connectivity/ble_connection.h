#ifndef BLE_CONNECTION_H
#define BLE_CONNECTION_H

#include <QObject>

#include <QLowEnergyService>

class QBluetoothDeviceInfo;
class QLowEnergyController;

class BLEConnection : public QObject
{
  Q_OBJECT

public:
  explicit BLEConnection(const QBluetoothUuid& serviceUUID,
                         const QBluetoothUuid& configurationUUID,
                         QObject* parent = nullptr);

  void connectToDevice(const QBluetoothDeviceInfo& deviceInfo);
  void disconnectFromDevice();

  void sendConfiguration(const QByteArray& data);

signals:
  void connected();
  void disconnected();
  void errorOccurred(const QString& errorMsg);
  void deviceReady();

private:
  QLowEnergyController* m_controller = nullptr;

  QLowEnergyService* m_service = nullptr;
  QLowEnergyCharacteristic m_configurationCharacteristic;

  const QBluetoothUuid& m_serviceUuid;
  const QBluetoothUuid& m_configurationUuid;
};

#endif // BLE_CONNECTION_H
