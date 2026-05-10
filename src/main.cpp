#include "Connectivity/ble_connection.h"
#include "Connectivity/ble_controller.h"
#include "Connectivity/ble_device_model.h"
#include "Connectivity/ble_scanner.h"

#include "Core/configuration.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);

  BLEScanner scanner;
  BLEDeviceModel deviceModel;
  BLEConnection connection;

  scanner.setFilter(QBluetoothUuid(Configuration::targetDeviceUUID));

  QObject::connect(&scanner,     &BLEScanner::deviceDiscovered,
                   &deviceModel, &BLEDeviceModel::addDevice);

  BLEController bleController(&scanner, &deviceModel, &connection);

  QQmlApplicationEngine engine;
  QQuickStyle::setStyle("Material");

  engine.rootContext()->setContextProperty("bleModel", &deviceModel);
  engine.rootContext()->setContextProperty("bleController", &bleController);

  QObject::connect(
    &engine,
    &QQmlApplicationEngine::objectCreationFailed,
    &app,
    []() { QCoreApplication::exit(-1); },
    Qt::QueuedConnection);

  engine.loadFromModule("MultiPlatformDemo", "Main");

  return app.exec();
}
