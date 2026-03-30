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
#include <taglib/tbytevectorstream.h>


FileReceiver::FileReceiver(AlbumCoverProvider *pManager,const QString& baseUrl, QObject *parent) : QObject{parent}, m_Manager{pManager}, m_BaseUrl{baseUrl}
{

}

OperationResult FileReceiver::getSongFromFile(const QUrl &file, QList<Song> &songs) const
{
    QString path{file.path()};
#ifdef Q_OS_WIN
    if (path.startsWith("/") && path[2] == ':') // e.g., "/C:/..."
        path = path.mid(1); // remove first slash
#endif


    const QFileInfo info{path};
    if(info.suffix().compare("zip", Qt::CaseInsensitive) == 0)
    {
        const OperationResult result {FileUtils::isZipFile(file)};

        if(!result.isSuccessful) return result;

        return getSongsFromZip(path,songs);
    }
    //TODO: Implement single file

    return OperationResult{};
}

OperationResult FileReceiver::getSongsFromZip(const QString &filePath, QList<Song> &songs) const
{
    OperationResult result;
    QuaZip zip(filePath);

    if (!zip.open(QuaZip::mdUnzip)) {
        result.isSuccessful = false;
        result.error = "Cannot open ZIP archive: " + filePath;
        return result;
    }

    QuaZipFile zipFile(&zip);
    QuaZipFileInfo fileInfo;

    QList<QString> errors{};
    bool bSucceeded{true};

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
            const auto result{getSongFromMP3(file,song)};

            if(!result.isSuccessful)
            {
                bSucceeded = false;
                errors << result.error;
                continue;
            }
            songs << song;

        }catch (std::exception& e){
            bSucceeded = false;
            errors << e.what();
        }
        zipFile.close();
    }

    result.isSuccessful = bSucceeded;

    if(!errors.empty())
    {
        result.error = QString("The following errors occured: %1").arg(errors.join("\n"));
    }
     return result;
}

OperationResult FileReceiver::getSongFromMP3(const TagLib::FileRef& fileRef,Song& song) const
{
    OperationResult result{};
    TagLib::File* file{fileRef.file()};
    if(TagLib::MPEG::File* mpegfile{dynamic_cast<TagLib::MPEG::File*>(file)})
    {

        if(mpegfile->hasID3v2Tag())
        {
            extractTagFromSong(mpegfile->ID3v2Tag(),file->name(),song);
            result.isSuccessful = true;
            return result;
        }

        if(mpegfile->hasID3v1Tag())
        {
            extractTagFromSong(mpegfile->ID3v1Tag(),file->name(),song);
            result.isSuccessful = true;
            return result;
        }

        if(mpegfile->hasAPETag())
        {
            extractTagFromSong(mpegfile->APETag(),file->name(),song);
            result.isSuccessful = true;
            return result;
        }

        result.isSuccessful = false;
        result.error = "Cannot read any tags from file. Add a valid mp3 file.";
        return result;
    }

    result.isSuccessful = false;
    result.error = "Cannot read any tags from file. Add a valid mp3 file.";
    return result;
}

void FileReceiver::extractTagFromSong(TagLib::Tag *tag, const TagLib::FileName &filename,Song& song) const
{
    extractTagTextData(tag,filename,song);
    song.albumCover = QUrl{m_BaseUrl + "/default"}; //no pictures supported
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
    }

    const QString& albumCoverId{QString{"%1-%2"}.arg(albumArtist,song.album)};
    song.albumCover = getAlbumCover(tag, albumCoverId);
}

void FileReceiver::extractTagTextData(TagLib::Tag *tag, const TagLib::FileName &filename, Song &song) const
{
    song.artists = tag->artist().toCString();
    song.album = tag->album().toCString();
    song.fileName = filename.toString().toCString();
    song.title = tag->title().toCString();
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
        return QString{m_BaseUrl + "/default"};
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
        return QString{m_BaseUrl + "/default"};
    }

    m_Manager->addImage(id,image);
    return albumUrl;
}



