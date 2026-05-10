#ifndef BLE_DEVICE_CONTROLLER_H
#define BLE_DEVICE_CONTROLLER_H

#include <QObject>

class BLEConnection;
class BLEDeviceModel;

class BLEDeviceController : public QObject
{
  Q_OBJECT

  Q_PROPERTY(bool isReady READ isReady NOTIFY isReadyChanged)
  Q_PROPERTY(QString statusMessage READ statusMessage NOTIFY statusMessageChanged)

public:
  BLEDeviceController(BLEConnection* connection, BLEDeviceModel* model, QObject* parent = nullptr);

  bool isReady() const;
  QString statusMessage() const;

  Q_INVOKABLE void connectToDevice(int index);
  Q_INVOKABLE void disconnectFromDevice();

  Q_INVOKABLE void sendLimit(int value);

signals:
  void isReadyChanged();
  void statusMessageChanged();

private:
  void setIsReady(bool status);
  void setStatusMessage(const QString& msg);

private:
  BLEConnection*  m_connection;
  BLEDeviceModel* m_model;

  bool m_isReady = false;
  QString m_statusMessage = "Waiting";
};

#endif // BLE_DEVICE_CONTROLLER_H
