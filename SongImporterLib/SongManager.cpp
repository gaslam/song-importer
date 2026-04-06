#include "SongManager.h"
#include "FileReceiver.h"

#include <QFuture>
#include <QtConcurrent>
#include <QSharedPointer>


SongManager::SongManager(QObject *parent)
    : QObject{parent}
{}

SongManager::~SongManager()
{
    quit();
}

void SongManager::addSong(const QString &filePath)
{

    process(filePath);
}

void SongManager::process(const QString& file)
{
    QFuture<void> value= QtConcurrent::run(SongManager::createWorker, this,file);
}

void SongManager::songProcessed(const Song &song)
{
    emit songReceived(song);
}

void SongManager::quit()
{
    emit stop();
}

void SongManager::createWorker(SongManager *manager,const QString& file)
{
    constexpr bool canExtractAlbumCovers{true};
    QSharedPointer<FileReceiver> provider{ new FileReceiver{file,"image://albumcover",canExtractAlbumCovers}};
    FileReceiver* receiver{provider.get()};
    connect(receiver,&FileReceiver::songProcessed,manager,&SongManager::songProcessed);
    connect(receiver,&FileReceiver::errorReceived,manager,&SongManager::errorReceived);
    receiver->getSongFromFile();
}
