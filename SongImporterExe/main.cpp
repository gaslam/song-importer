#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <SongImporterLib_global.h>
#include <SongImporterLib.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("SongImporterExe", "Main");

    return app.exec();
}
