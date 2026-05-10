#include "ble_discovery_controller.h"

#include "ble_device_model.h"
#include "ble_scanner.h"

BLEDiscoveryController::BLEDiscoveryController(BLEScanner* scanner, BLEDeviceModel* model, QObject* parent)
  : QObject(parent)
  , m_scanner(scanner)
  , m_model(model)
{
  connect(m_scanner, &BLEScanner::scanFinished,
          this,      [this]()
  {
    m_isScanning = false;
    emit isScanningChanged();
  });
}

bool BLEDiscoveryController::isScanning() const
{
  return m_isScanning;
}

void BLEDiscoveryController::startScan()
{
  m_isScanning = true;
  emit isScanningChanged();

  m_model->clear();
  m_scanner->startScan();
}

void BLEDiscoveryController::stopScan()
{
  m_scanner->stopScan();

  m_isScanning = false;
  emit isScanningChanged();
}
