#ifndef BLE_DEVICE_MODEL_H
#define BLE_DEVICE_MODEL_H

#include <QAbstractListModel>
#include <QBluetoothDeviceInfo>

class BLEDeviceModel : public QAbstractListModel
{
  Q_OBJECT

public:
  enum DeviceRoles
  {
    NameRole = Qt::UserRole + 1,
    AddressRole,
    ConnectableRole
  };

  explicit BLEDeviceModel(QObject* parent = nullptr);

  int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;

  QBluetoothDeviceInfo getDevice(int index) const;

public slots:
  void addDevice(const QBluetoothDeviceInfo& device);
  void clear();

private:
  QList<QBluetoothDeviceInfo> m_devices;
};

#endif // BLE_DEVICE_MODEL_H
