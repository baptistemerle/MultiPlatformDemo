#ifndef BLE_DEVICE_CONTROLLER_H
#define BLE_DEVICE_CONTROLLER_H

#include <QObject>

class BLEConnection;
class BLEDeviceModel;

class BLEDeviceController : public QObject
{
  Q_OBJECT

public:
  BLEDeviceController(BLEConnection* connection, BLEDeviceModel* model, QObject* parent = nullptr);

  Q_INVOKABLE void connectToDevice(int index);
  Q_INVOKABLE void disconnectFromDevice();

  Q_INVOKABLE void sendLimit(int value);

private:
  BLEConnection*  m_connection;
  BLEDeviceModel* m_model;
};

#endif // BLE_DEVICE_CONTROLLER_H
