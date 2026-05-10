#include "Connectivity/ble_connection.h"
#include "Connectivity/ble_device_controller.h"
#include "Connectivity/ble_device_model.h"
#include "Connectivity/ble_discovery_controller.h"
#include "Connectivity/ble_scanner.h"

#include "Core/alert_controller.h"
#include "Core/configuration.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);

  AlertController alertController;
  BLEScanner scanner;
  BLEDeviceModel deviceModel;
  BLEConnection connection(Configuration::targetServiceUUID, Configuration::configurationDeviceUUID);

  scanner.setFilter(QBluetoothUuid(Configuration::targetServiceUUID));

  QObject::connect(&scanner,     &BLEScanner::deviceDiscovered,
                   &deviceModel, &BLEDeviceModel::addDevice);

  QObject::connect(&scanner,         &BLEScanner::scanError,
                   &alertController, &AlertController::showError);

  QObject::connect(&connection,      &BLEConnection::errorOccurred,
                   &alertController, &AlertController::showError);

  BLEDiscoveryController discoveryController(&scanner, &deviceModel);
  BLEDeviceController deviceController(&connection, &deviceModel);

  QQmlApplicationEngine engine;
  QQuickStyle::setStyle("Material");

  engine.rootContext()->setContextProperty("bleModel", &deviceModel);
  engine.rootContext()->setContextProperty("discoveryController", &discoveryController);
  engine.rootContext()->setContextProperty("deviceController", &deviceController);
  engine.rootContext()->setContextProperty("alertController", &alertController);

  QObject::connect(
    &engine,
    &QQmlApplicationEngine::objectCreationFailed,
    &app,
    []() { QCoreApplication::exit(-1); },
    Qt::QueuedConnection);

  engine.loadFromModule("MultiPlatformDemo", "Main");

  return app.exec();
}
