#include "SongList.h"
#include "FileUtils.h"
#include <algorithm>


SongList::SongList(QObject *parent)
    : QAbstractListModel{parent}
{

    connect(&m_Manager,&Manager::songReceived,this,&SongList::addSong);
}

int SongList::columnCount(const QModelIndex &) const
{
    return 5;
}

int SongList::rowCount(const QModelIndex &parent) const
{
    return static_cast<int>(m_Songs.size());
}

QVariant SongList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_Songs.size())
        return QVariant();

    const Song &song = m_Songs.at(index.row());
    switch(role) {
    case TitleRole:
        return song.title;
    case ArtistsRole:
        return song.artists;
    case YearRole:
        return song.year;
    case AlbumCoverRole:
        return song.albumCover;
    case AlbumRole:
        return song.album;
    default:
        return QVariant();
    }
}

OperationResult SongList::addSong(const Song &song)
{
    if(m_Songs.contains(song))
    {
        const QString error{QString{"Cannot add song: %1 by %2. Song is already in list."}.arg(song.title,song.artists)};
        emit errorReceived(error);
        return OperationResult::fail(error);
    }
    beginInsertRows(QModelIndex(), m_Songs.size(),m_Songs.size());
    m_Songs << song;

    endInsertRows();
    return OperationResult::succeed();
}

/*OperationResult SongList::addSongs(const QList<Song> &songs)
{

    QList<Song> newSongs;
    QList<QString> errors;
    foreach(const Song& song, songs){
        if(newSongs.contains(song))
        {
            QString error{QString{"Cannot add song: %1 by %2. Song is already in list."}.arg(song.title,song.artists)};
            errors << error;
        }
        else
        {
            newSongs << song;
        }
    };

    if(!newSongs.isEmpty())
    {
        int start = m_Songs.size();
        int end = start + newSongs.size() - 1;
        beginInsertRows(QModelIndex(), start, end);
        m_Songs << newSongs;
        endInsertRows();
    }

    if(!errors.isEmpty())
    {
        const QString error{QString{"The following errors have been occurred: %1"}.arg(errors.join("\n"))};
        return OperationResult::fail(error);
    }

    return OperationResult::succeed();
}*/


QHash<int, QByteArray> SongList::roleNames() const
{
    return {
        { YearRole, "year" },
        { ArtistsRole, "artists" },
        { TitleRole, "title" },
        {AlbumCoverRole, "albumCover"},
        {AlbumRole, "album"}
    };
}

void SongList::extractSongsFromFiles(const QList<QUrl> &files)
{
    QList<Song> songs;

    foreach(const auto& file, files)
    {
        QString path{file.path()};
#ifdef Q_OS_WIN
        if (path.startsWith("/") && path[2] == ':') // e.g., "/C:/..."
            path = path.mid(1); // remove first slash
#endif

        OperationResult result {};
        const QFileInfo info{path};

        if(info.suffix().compare("mp3",Qt::CaseInsensitive) == 0)
        {
            m_Manager.addSong(path);
        }

        /*if(info.suffix().compare("zip", Qt::CaseInsensitive) == 0)
        {
            result = FileUtils::isZipFile(file);

            if(!result.isSuccessful) break;

            result = m_Receiver->getSongsFromZip(path,songs);
        }
        else
        {
            result = m_Receiver->getSongFromFile(path,songs);
        }

        if(!result.isSuccessful)
        {
            emit errorReceived(result.error);
        }*/
    }

}
