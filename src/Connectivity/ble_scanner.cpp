#include "ble_scanner.h"

#include <QBluetoothDeviceDiscoveryAgent>

BLEScanner::BLEScanner(QObject* parent)
  : QObject(parent)
  , m_discoveryAgent(new QBluetoothDeviceDiscoveryAgent(this))
{
  connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
          this,             [this](const QBluetoothDeviceInfo& info)
          {
            if (m_filter.isNull() || info.serviceUuids().contains(m_filter))
            {
              emit deviceDiscovered(info);
            }
          });

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

void BLEScanner::setFilter(const QBluetoothUuid targetServiceUuid)
{
  m_filter = targetServiceUuid;
}

void BLEScanner::clearFilter()
{
  m_filter = QBluetoothUuid();
}