#ifndef FILERECEIVER_H
#define FILERECEIVER_H

#include "OperationResult.h"
#include "SongImporterLib_global.h"
#include "AlbumCoverProvider.h"
#include <QObject>
#include <QUrl>
#include <taglib/taglib.h>
#include <taglib/fileref.h>

struct SONGIMPORTERLIB_EXPORT Song {

    Q_GADGET
    Q_PROPERTY(QString title MEMBER title)
    Q_PROPERTY(QString artists MEMBER artists)
    Q_PROPERTY(QString filename MEMBER fileName)
    Q_PROPERTY(QString album MEMBER album)
    Q_PROPERTY(QUrl albumCover MEMBER albumCover)
    Q_PROPERTY(unsigned int year MEMBER year)
public:
    unsigned int year;
    QString title;
    QString album;
    QUrl albumCover;
    QString artists;
    QString fileName;
};

Q_DECLARE_METATYPE(Song)

class SONGIMPORTERLIB_EXPORT FileReceiver : public QObject
{
    Q_OBJECT
public:
    FileReceiver(AlbumCoverProvider* m_Manager, QObject* parent = nullptr);
public slots:
    [[nodiscard]] OperationResult getSongFromFile(const QUrl& file,Song& song);

private:
    [[nodiscard]] OperationResult getSongFromMP3 (TagLib::File* file,Song& song);
    void extractTagFromSong(TagLib::Tag* tag,const TagLib::FileName& filename,Song& song);

    AlbumCoverProvider* m_Manager;
};

#endif // FILERECEIVER_H
