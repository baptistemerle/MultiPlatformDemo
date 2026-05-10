#ifndef BLE_CONTROLLER_H
#define BLE_CONTROLLER_H

#include <QObject>

class BLEScanner;
class BLEDeviceModel;
class BLEConnection;

class BLEController : public QObject
{
  Q_OBJECT

  Q_PROPERTY(bool isScanning READ isScanning NOTIFY isScanningChanged)

public:
  BLEController(BLEScanner* scanner, BLEDeviceModel* model, BLEConnection* connection, QObject* parent = nullptr);

  bool isScanning() const;

  Q_INVOKABLE void startScan();
  Q_INVOKABLE void stopScan();

  Q_INVOKABLE void connectToDevice(int index);
  Q_INVOKABLE void disconnectFromDevice();

  Q_INVOKABLE void sendLimit(int value);

signals:
  void isScanningChanged();

private:
  BLEScanner* m_scanner;
  BLEDeviceModel* m_model;
  BLEConnection* m_connection;

  bool m_isScanning = false;
};

#endif // BLE_CONTROLLER_H
