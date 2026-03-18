#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <SongImporterLib_global.h>
#include <InputValidator.h>
#include <FolderValidator.h>
#include <FileValidator.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<FolderValidator>("SongImporter.Validators", 1, 0, "FolderValidator");
    qRegisterMetaType<ValidationResult>("validationResult");
    qmlRegisterType<FileValidator>("SongImporter.Validators", 1, 0, "FileValidator");
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
