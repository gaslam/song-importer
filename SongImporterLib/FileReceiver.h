#ifndef FILERECEIVER_H
#define FILERECEIVER_H

#include "OperationResult.h"
#include "SongImporterLib_global.h"
#include "AlbumCoverProvider.h"
#include <QObject>
#include <QUrl>
#include <qfileinfo.h>
#include <taglib/taglib.h>
#include <taglib/fileref.h>
#include <taglib/id3v2tag.h>

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

    bool operator==(const Song& other) const
    {
        const bool bIsSameFile{this->fileName == other.fileName};

        return bIsSameFile;
    }

    bool operator==(const QString& fileName) const
    {
        return this->fileName == fileName;
    }
};

Q_DECLARE_METATYPE(Song)

class SONGIMPORTERLIB_EXPORT FileReceiver : public QObject
{
    Q_OBJECT
public:
    FileReceiver(AlbumCoverProvider* m_Manager, const QString& baseUrl, QObject* parent = nullptr);
    [[nodiscard]] OperationResult getSongFromFile(const QString& filePath,QList<Song>& songs) const;
    [[nodiscard]] OperationResult getSongsFromZip(const QString &filePath, QList<Song> &songs) const;
public slots:

private:
    [[nodiscard]] OperationResult getSongFromFileRef (const TagLib::FileRef& file,Song& song) const;
    [[nodiscard]] QString getAlbumCover(TagLib::ID3v2::Tag* tag,const QString& id) const;
    void extractTagFromSong(TagLib::ID3v2::Tag* tag,const TagLib::FileName& filename,Song& song) const;
    void extractTagFromSong(TagLib::Tag* tag,const TagLib::FileName& filename,Song& song) const;
    void extractTagTextData(TagLib::Tag* tag, const TagLib::FileName &filename,Song& song) const;

    const QString m_BaseUrl;

    AlbumCoverProvider* m_Manager;
    /*OperationResult extractPictureFromTag(TagLib::ID3v2::Tag *tag, const QString &albumCover);*/
};

#endif // FILERECEIVER_H
