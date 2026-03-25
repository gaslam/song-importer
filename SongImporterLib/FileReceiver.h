#ifndef FILERECEIVER_H
#define FILERECEIVER_H

#include "OperationResult.h"
#include "SongImporterLib_global.h"
#include <QObject>
#include <QUrl>
#include <taglib/taglib.h>
#include <taglib/fileref.h>

struct SONGIMPORTERLIB_EXPORT Song {

    Q_GADGET
    Q_PROPERTY(QString title MEMBER title)
    Q_PROPERTY(QString artists MEMBER artists)
    Q_PROPERTY(QString filename MEMBER fileName)
     Q_PROPERTY(unsigned int year MEMBER year)
public:
    unsigned int year;
    QString title;
    QUrl albumCover;
    QString artists;
    QString fileName;
};

Q_DECLARE_METATYPE(Song)

class SONGIMPORTERLIB_EXPORT FileReceiver : public QObject
{
    Q_OBJECT
public:
    FileReceiver();
public slots:
    [[nodiscard]] Song getSongFromFile(const QUrl& file);

private:
    [[nodiscard]] OperationResult getSongFromMP3 (TagLib::File* file,Song& song);
    void extractTagFromSong(TagLib::Tag* tag,const TagLib::FileName& filename,Song& song);
};

#endif // FILERECEIVER_H
