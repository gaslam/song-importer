#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <SongImporterLib_global.h>
#include <InputValidator.h>
#include <FolderValidator.h>
#include <FileValidator.h>
#include <FileUtils.h>
#include <FileReceiver.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<FolderValidator>("SongImporter.Validators", 1, 0, "FolderValidator");
    qRegisterMetaType<OperationResult>("operationResult");
    qRegisterMetaType<Song>("song");
    qmlRegisterType<FileValidator>("SongImporter.Validators", 1, 0, "FileValidator");
    qmlRegisterType<FileReceiver>("SongImporter.FileReceiver", 1, 0, "FileReceiver");
    qmlRegisterSingletonType<FileUtils>("SongImporter.Utils", 1, 0, "FileUtils",
                                        [&app](QQmlEngine *, QJSEngine *) -> QObject* {
                                            return new FileUtils(&app);
                                        });
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
