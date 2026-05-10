#ifndef BLE_DISCOVERY_CONTROLLER_H
#define BLE_DISCOVERY_CONTROLLER_H

#include <QObject>

class BLEScanner;
class BLEDeviceModel;

class BLEDiscoveryController : public QObject
{
  Q_OBJECT

  Q_PROPERTY(bool isScanning READ isScanning NOTIFY isScanningChanged)

public:
  BLEDiscoveryController(BLEScanner* scanner, BLEDeviceModel* model, QObject* parent = nullptr);

  bool isScanning() const;

  Q_INVOKABLE void startScan();
  Q_INVOKABLE void stopScan();

signals:
  void isScanningChanged();

private:
  BLEScanner*     m_scanner;
  BLEDeviceModel* m_model;

  bool m_isScanning = false;
};

#endif // BLE_DISCOVERY_CONTROLLER_H
