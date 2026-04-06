#include "FileReceiver.h"
#include "FileUtils.h"

#include <taglib/mpegfile.h>

#include <APETag.h>
#include <ID3v1Tag.h>
#include<id3v2frame.h>//frame
#include <attachedPictureFrame.h>//attachedPictureFrame
#include <AttachedPictureFrame.h>
#include <textidentificationframe.h>
#include <QuaZip.h>
#include <QuaZipFile.h>
#include <XiphComment.h>
#include <taglib/tbytevectorstream.h>


FileReceiver::FileReceiver(const QString& file,const QString& baseUrl,bool canExtractAlbumCovers, QObject *parent) : QObject{parent},
    m_CanExtractAlbumCovers{canExtractAlbumCovers},
    m_Manager{AlbumCoverProvider::Instance()},
    m_FileToProcess{file},
    m_BaseUrl{baseUrl},
    m_DefaultUrl{baseUrl + "/default"}
{

}

void FileReceiver::getSongFromFile()
{
    TagLib::FileRef file{m_FileToProcess.toStdString().c_str()};

    if(file.isNull())
    {
        emit errorReceived(QString{"Cannot read file: %1."}.arg(m_FileToProcess));
        return;
    }

    Song song;
    auto result{ getSongFromFileRef(file,song)};

    if(!result.isSuccessful)
    {
        emit errorReceived(result.error);
    }

    emit songProcessed(song);
}





/*OperationResult FileReceiver::getSongsFromZip(const QString &filePath, QList<Song> &songs) const
{
    QuaZip zip(filePath);

    if (!zip.open(QuaZip::mdUnzip)) {

        const QString error{ "Cannot open ZIP archive: " + filePath};
        return OperationResult::fail(error);
    }

    QuaZipFile zipFile(&zip);
    QuaZipFileInfo fileInfo;

    QList<QString> errors{};

    for(bool i{zip.goToFirstFile()}; i; i = zip.goToNextFile())
    {
        if (!zip.getCurrentFileInfo(&fileInfo)) continue;

        if (!zipFile.open(QIODevice::ReadOnly)) {
            qWarning() << "Failed to open:" << fileInfo.name;
            continue;
        }

        QByteArray data{zipFile.readAll()};

        try{
            TagLib::ByteVector bv(data.constData(), data.size());
            TagLib::ByteVectorStream memStream(bv);
            TagLib::FileRef file{&memStream};
            Song song;
            const auto result{getSongFromFileRef(file,song)};

            if(!result.isSuccessful)
            {
                errors << result.error;
                continue;
            }
            songs << song;

        }catch (std::exception& e){
            errors << QString{"%1 for file: %2"}.arg(e.what(),filePath);
        }
        zipFile.close();
    }

    if(!errors.empty())
    {
        const QString error {QString("The following errors occured: %1").arg(errors.join("\n"))};
        return OperationResult::fail(error);
    }
    return OperationResult::succeed();
}*/

OperationResult FileReceiver::getSongFromFileRef(const TagLib::FileRef& fileRef,Song& song) const
{
    TagLib::File* file{fileRef.file()};
    if(TagLib::MPEG::File* mpegfile{dynamic_cast<TagLib::MPEG::File*>(file)})
    {

        if(mpegfile->hasID3v2Tag())
        {
            extractTagFromSong(mpegfile->ID3v2Tag(),file->name(),song);
            return OperationResult::succeed();
        }

        if(mpegfile->hasID3v1Tag())
        {
            extractTagFromSong(mpegfile->ID3v1Tag(),file->name(),song);
            return OperationResult::succeed();
        }

        if(mpegfile->hasAPETag())
        {
            extractTagFromSong(mpegfile->APETag(),file->name(),song);
            return OperationResult::succeed();
        }
        extractTagFromSong(mpegfile->tag(),file->name(),song);
        return OperationResult::succeed();
    }

    if(TagLib::FLAC::File* flacFile{dynamic_cast<TagLib::FLAC::File*>(file)})
    {
        return getSongFromFlacFile(flacFile,song);
    }

    const QString error{  "Cannot read any tags from file. Add a valid audio file."};
    return OperationResult::fail(error);
}

OperationResult FileReceiver::getSongFromFlacFile(TagLib::FLAC::File *file, Song &song) const
{
    TagLib::Ogg::XiphComment* tag = file->xiphComment(false);
    extractTagTextData(tag,file->name(),song);
    QString albumId{""};
    if (tag) {
        auto test = tag->fieldListMap();

        TagLib::StringList albumArtists {test["ISRC"]};

        if (albumArtists.isEmpty()) {
            albumArtists = test["ALBUMARTIST"];
            if (albumArtists.isEmpty()) {
                auto artist{tag->artist()};
                if(artist.isEmpty()) artist = "Unknown Artist";
                albumArtists.append(artist);
            }
             const QString& albumCoverId{QString{"%1-%2"}.arg(albumArtists.front().toCString(),song.album)};
        }

        albumId = QString::fromStdString(albumArtists.front().to8Bit(true));
    }

    if(m_CanExtractAlbumCovers)
    {
        QString albumCover{getAlbumCover(file,albumId)};

        if(!albumCover.isEmpty())
        {
            song.albumCover = albumCover;
            return OperationResult::succeed();
        }
    }

    if(file->hasID3v2Tag())
    {
        song.albumCover = getAlbumCover(file->ID3v2Tag(),albumId);
        return OperationResult::succeed();
    }
        song.albumCover = m_DefaultUrl;
        return OperationResult::succeed();

}

void FileReceiver::extractTagFromSong(TagLib::Tag *tag, const TagLib::FileName &filename,Song& song) const
{
    extractTagTextData(tag,filename,song);
    song.albumCover = QUrl{m_DefaultUrl}; //no pictures supported
}

void FileReceiver::extractTagFromSong(TagLib::ID3v2::Tag *tag, const TagLib::FileName &filename,Song& song) const
{

    extractTagTextData(tag,filename,song);
    auto frames = tag->frameList("TPE2"); // Album Artist

    QString albumArtist{"Various Artists"};

    if (!frames.isEmpty())
    {
        auto frame = dynamic_cast<TagLib::ID3v2::TextIdentificationFrame*>(frames.front());
        if (frame)
        {
            albumArtist = QString::fromStdString(frame->toString().to8Bit(true));
        }
        else
        {
            albumArtist = song.artists;
        }
    }
    else
    {
        albumArtist = song.artists;
    }

    const QString& albumCoverId{QString{"%1-%2"}.arg(albumArtist,song.album)};

    if(m_CanExtractAlbumCovers)
    {
        song.albumCover = getAlbumCover(tag, albumCoverId);
    }
    else
    {
        song.albumCover = m_DefaultUrl;
    }
}

void FileReceiver::extractTagTextData(TagLib::Tag *tag, const TagLib::FileName &filename, Song &song) const
{
    song.artists = tag->artist().toCString();
    song.album = tag->album().toCString();
    song.fileName = filename.toString().toCString();

    QString title{tag->title().toCString()};
    if(title.isEmpty()) title = QFileInfo{filename.toString().toCString()}.baseName().replace('_', ' ');
    song.title = title;
    song.year = tag->year();
}

QString FileReceiver::getAlbumCover(TagLib::ID3v2::Tag* tag,const QString& id) const
{
    const QString albumUrl{m_BaseUrl + "/" + id};
    if(m_Manager->hasImage(id))
    {
        return albumUrl;
    }
    const TagLib::ID3v2::FrameList& frameList{tag->frameList("APIC")};
    if(frameList.isEmpty())
    {
        return m_DefaultUrl;
    }
    auto pictureFrame = static_cast<TagLib::ID3v2::AttachedPictureFrame *> (frameList.front());

    const TagLib::ByteVector data = pictureFrame->picture();

    QImage image;
    image.loadFromData(
        reinterpret_cast<const uchar*>(data.data()),
        data.size()
        );
    if(image.isNull())
    {
        return m_DefaultUrl;
    }

    m_Manager->addImage(id,image);
    return albumUrl;
}

QString FileReceiver::getAlbumCover(TagLib::FLAC::File* file, const QString &id) const
{
    const QString albumUrl{m_BaseUrl + "/" + id};
    if(m_Manager->hasImage(id))
    {
        return albumUrl;
    }

    auto picList{file->pictureList()};

    if (picList.isEmpty())
        return QString{};

    TagLib::FLAC::Picture* pic = picList.front();

    const TagLib::ByteVector& data = pic->data();

    QImage image { QImage::fromData(
        reinterpret_cast<const uchar*>(data.data()),
        data.size()
        )};

    m_Manager->addImage(id,image);

    return albumUrl;
}



