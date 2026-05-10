#ifndef BLE_SCANNER_H
#define BLE_SCANNER_H

#include <QObject>
#include <QBluetoothUuid>

class QBluetoothDeviceDiscoveryAgent;
class QBluetoothDeviceInfo;

class BLEScanner : public QObject
{
  Q_OBJECT

public:
  explicit BLEScanner(QObject* parent = nullptr);

  void startScan();
  void stopScan();

  void setFilter(const QBluetoothUuid targetServiceUuid);
  void clearFilter();

signals:
  void deviceDiscovered(const QBluetoothDeviceInfo& device);
  void scanFinished();
  void scanError(const QString& errorString);

private:
  QBluetoothDeviceDiscoveryAgent* m_discoveryAgent;
  QBluetoothUuid m_filter;
};

#endif // BLE_SCANNER_H