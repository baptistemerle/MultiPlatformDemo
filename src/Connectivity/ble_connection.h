#ifndef BLE_CONNECTION_H
#define BLE_CONNECTION_H

#include <QObject>

class QBluetoothDeviceInfo;
class QLowEnergyController;

class BLEConnection : public QObject
{
  Q_OBJECT

public:
  explicit BLEConnection(QObject* parent = nullptr);

  void connectToDevice(const QBluetoothDeviceInfo& deviceInfo);
  void disconnectFromDevice();

signals:
  void connected();
  void disconnected();
  void errorOccurred(const QString& errorMsg);

private:
  QLowEnergyController* m_controller = nullptr;
};

#endif // BLE_CONNECTION_H
