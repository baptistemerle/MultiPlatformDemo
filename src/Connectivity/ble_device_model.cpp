#include "ble_device_model.h"

#include <QBluetoothAddress>

BLEDeviceModel::BLEDeviceModel(QObject* parent)
  : QAbstractListModel(parent)
{
}

int BLEDeviceModel::rowCount(const QModelIndex& parent) const
{
  if (parent.isValid())
  {
    return 0;
  }

  return m_devices.size();
}

QVariant BLEDeviceModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid() || index.row() >= m_devices.size())
  {
    return QVariant();
  }

  const QBluetoothDeviceInfo &device = m_devices.at(index.row());

  switch (role)
  {
  case NameRole:
    return device.name().isEmpty() ? "Unknown device" : device.name();
  case AddressRole:
    return device.address().toString();
  case ConnectableRole:
    return device.coreConfigurations().testFlag(QBluetoothDeviceInfo::LowEnergyCoreConfiguration);
  default:
    return QVariant();
  }
}

QHash<int, QByteArray> BLEDeviceModel::roleNames() const
{
  QHash<int, QByteArray> roles;

  roles[NameRole] = "deviceName";
  roles[AddressRole] = "deviceAddress";
  roles[ConnectableRole] = "isConnectable";

  return roles;
}

QBluetoothDeviceInfo BLEDeviceModel::getDevice(int index) const
{
  if (index < 0 || index >= m_devices.size())
  {
    return QBluetoothDeviceInfo();
  }

  return m_devices.at(index);
}

void BLEDeviceModel::addDevice(const QBluetoothDeviceInfo& device)
{
  for (const auto &d : std::as_const(m_devices))
  {
    if (d.address() == device.address())
    {
      return;
    }
  }

  beginInsertRows(QModelIndex(), m_devices.size(), m_devices.size());
  m_devices.append(device);
  endInsertRows();
}

void BLEDeviceModel::clear()
{
  if (m_devices.isEmpty())
    return;

  beginResetModel();
  m_devices.clear();
  endResetModel();
}
