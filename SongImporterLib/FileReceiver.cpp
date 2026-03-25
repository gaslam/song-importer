#include "FileReceiver.h"
#include "FileUtils.h"

#include <taglib/mpegfile.h>

#include <APETag.h>
#include <ID3v1Tag.h>
#include <ID3v2Tag.h>


FileReceiver::FileReceiver() {}

Song FileReceiver::getSongFromFile(const QUrl &file)
{
    QString path{file.path()};
#ifdef Q_OS_WIN
    if (path.startsWith("/") && path[2] == ':') // e.g., "/C:/..."
        path = path.mid(1); // remove first slash
#endif
    const QFileInfo info{path};
    const QString suffixLower{info.suffix().toLower()};

    Song song;

    OperationResult result{};
    Q_UNUSED(result)

    if(info.suffix().toLower() == "zip")
    {
        result = FileUtils::isZipFile(file);

        if(!result.isSuccessful) return song;
    }

    TagLib::FileRef f{path.toUtf8().constData()};

    if(f.isNull())
    {
        OperationResult result{};
        result.isSuccessful = false;
        result.error = "Cannot read file at location " + path;
        return song;
    }
    TagLib::File* audioFile{f.file()};

    if(info.suffix() == "mp3")
    {
        auto test = getSongFromMP3(audioFile,song);
        Q_UNUSED(test);
        return song;
    }

    result.error = "Cannot read audio file!";
    result.isSuccessful = false;
    return song;
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
    song.fileName = filename.toString().toCString();
    song.title = tag->title().toCString();
    song.year = tag->year();
}



