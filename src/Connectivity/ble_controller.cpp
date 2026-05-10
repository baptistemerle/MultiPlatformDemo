#include "ble_controller.h"

#include "ble_connection.h"
#include "ble_device_model.h"
#include "ble_scanner.h"

BLEController::BLEController(BLEScanner* scanner, BLEDeviceModel* model, BLEConnection* connection, QObject* parent)
  : QObject(parent)
  , m_scanner(scanner)
  , m_model(model)
  , m_connection(connection)
{
  connect(m_scanner, &BLEScanner::scanFinished, this, [this]()
  {
    m_isScanning = false;
    emit isScanningChanged();
  });
}

bool BLEController::isScanning() const
{
  return m_isScanning;
}

void BLEController::startScan()
{
  m_isScanning = true;
  emit isScanningChanged();

  m_model->clear();
  m_scanner->startScan();
}

void BLEController::stopScan()
{
  m_scanner->stopScan();

  m_isScanning = false;
  emit isScanningChanged();
}

void BLEController::connectToDevice(int index)
{
  QBluetoothDeviceInfo device = m_model->getDevice(index);

  if (device.isValid())
  {
    m_connection->connectToDevice(device);
  }
}

void BLEController::disconnectFromDevice()
{
  m_connection->disconnectFromDevice();
}

void BLEController::sendLimit(int value)
{
  // TODO make this part clean
  QString jsonPart = QString("{\"limit\":%1}").arg(value);
  int jsonSize = jsonPart.toUtf8().size();
  QString sizePrefix = QString("%1").arg(jsonSize, 4, 10, QChar('0'));
  QString finalPayload = sizePrefix + jsonPart;

  m_connection->sendConfiguration(finalPayload.toUtf8());
}
