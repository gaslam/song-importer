#include "FileReceiver.h"
#include "FileUtils.h"

#include <taglib/mpegfile.h>

#include <APETag.h>
#include <ID3v1Tag.h>
#include <ID3v2Tag.h>


FileReceiver::FileReceiver(AlbumCoverProvider *pManager, QObject *parent) : QObject{parent}, m_Manager{pManager}
{

}

OperationResult FileReceiver::getSongFromFile(const QUrl &file,Song& song)
{
    QString path{file.path()};
#ifdef Q_OS_WIN
    if (path.startsWith("/") && path[2] == ':') // e.g., "/C:/..."
        path = path.mid(1); // remove first slash
#endif
    const QFileInfo info{path};
    const QString suffixLower{info.suffix().toLower()};

    OperationResult result{};

    if(info.suffix().toLower() == "zip")
    {
        result = FileUtils::isZipFile(file);

        if(!result.isSuccessful) return result;
    }

    TagLib::FileRef f{path.toUtf8().constData()};

    if(f.isNull())
    {
        OperationResult result{};
        result.isSuccessful = false;
        result.error = "Cannot read file at location " + path;
        return result;
    }
    TagLib::File* audioFile{f.file()};

    if(info.suffix() == "mp3")
    {
        result = getSongFromMP3(audioFile,song);
        return result;
    }

    result.error = "Cannot read audio file!";
    result.isSuccessful = false;
    return result;
}

OperationResult FileReceiver::getSongFromMP3( TagLib::File *file,Song& song)
{
    OperationResult result{};
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

void FileReceiver::extractTagFromSong(TagLib::Tag *tag, const TagLib::FileName &filename,Song& song)
{
    song.artists = tag->artist().toCString();
    song.album = tag->album().toCString();
    song.fileName = filename.toString().toCString();
    song.title = tag->title().toCString();
    song.year = tag->year();
    song.albumCover = QUrl{"image://albumcover/test"};
}



