#include "ble_scanner.h"

#include <QBluetoothDeviceDiscoveryAgent>

BLEScanner::BLEScanner(QObject* parent)
  : QObject(parent)
  , m_discoveryAgent(new QBluetoothDeviceDiscoveryAgent(this))
{
  connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
          this,             &BLEScanner::deviceDiscovered);

  connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished,
          this,             &BLEScanner::scanFinished);

  connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::errorOccurred,
          this,             [this](QBluetoothDeviceDiscoveryAgent::Error error)
          {
            Q_UNUSED(error)
            emit scanError(m_discoveryAgent->errorString());
          });
}

void BLEScanner::startScan()
{
  if (!m_discoveryAgent->isActive())
  {
    m_discoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
  }
}

void BLEScanner::stopScan()
{
  if (m_discoveryAgent->isActive())
  {
    m_discoveryAgent->stop();
  }
}