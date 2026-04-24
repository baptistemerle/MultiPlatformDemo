#ifndef BLE_SCANNER_H
#define BLE_SCANNER_H

#include <QObject>

class QBluetoothDeviceDiscoveryAgent;
class QBluetoothDeviceInfo;

class BLEScanner : public QObject
{
  Q_OBJECT

public:
  explicit BLEScanner(QObject* parent = nullptr);

  void startScan();
  void stopScan();

signals:
  void deviceDiscovered(const QBluetoothDeviceInfo& device);
  void scanFinished();
  void scanError(const QString& errorString);

private:
  QBluetoothDeviceDiscoveryAgent* m_discoveryAgent;
};

#endif // BLE_SCANNER_H