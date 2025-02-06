#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>
#include "soundcore/App.hpp"


int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQmlContext * context = engine.rootContext();

    qmlRegisterUncreatableType<App>("App", 1, 0, "App", "App class");
    qmlRegisterUncreatableType<DeviceDiscoverer>("DeviceDiscoverer", 1, 0, "DeviceDiscoverer", "");
    qmlRegisterUncreatableType<DiscoveredDevicesInfoListModel>("DiscoveredDevicesInfoListModel", 1, 0, "DiscoveredDevicesInfoListModel","");
    qmlRegisterUncreatableType<DeviceConnector>("DeviceConnector", 1, 0, "DeviceConnector","");
    qmlRegisterUncreatableType<Device>("Device", 1, 0, "Device","");
    qmlRegisterUncreatableType<DeviceController>("DeviceController", 1, 0, "DeviceController","");

    DeviceDiscoverer deviceDiscoverer;
    DiscoveredDevicesInfoListModel discoveredDevicesInfoListModel;
    DeviceController deviceController;
    auto soundcoreApp = new App(deviceDiscoverer, discoveredDevicesInfoListModel, deviceController);

    engine.rootContext()->setContextProperty("deviceDiscoverer", &deviceDiscoverer);
    engine.rootContext()->setContextProperty("discoveredDevicesInfoListModel", &discoveredDevicesInfoListModel);
    engine.rootContext()->setContextProperty("deviceController", &deviceController);
    engine.rootContext()->setContextProperty("soundcoreApp", soundcoreApp);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app, []() { QCoreApplication::exit(-1); },
                     Qt::QueuedConnection);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));


    return app.exec();
}