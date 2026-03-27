#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <SongImporterLib_global.h>
#include <InputValidator.h>
#include <FolderValidator.h>
#include <FileValidator.h>
#include <FileUtils.h>
#include <FileReceiver.h>
#include <SongList.h>
#include <AlbumCoverProvider.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<FolderValidator>("SongImporter.Validators", 1, 0, "FolderValidator");
    qRegisterMetaType<Song>("song");
    qmlRegisterType<FileValidator>("SongImporter.Validators", 1, 0, "FileValidator");
    qmlRegisterSingletonType<FileUtils>("SongImporter.Utils", 1, 0, "FileUtils",
                                        [&app](QQmlEngine *, QJSEngine *) -> QObject* {
                                            return new FileUtils(&app);
    });

    QString defaultString{"default"};
    QImage defaultImage{":/icons/logo-icon.png"};

        AlbumCoverProvider* provider = new AlbumCoverProvider(defaultString,defaultImage);
    SongList* model{new SongList{new FileReceiver{provider,&app},&app}};
    qmlRegisterSingletonInstance("SongImporter.SongListModel",1,0,"SongListModel",model);
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.addImageProvider("albumcover", provider);

    engine.loadFromModule("SongImporterExe", "Main");

    return app.exec();
}
