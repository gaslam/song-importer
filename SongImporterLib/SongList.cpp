#include "SongList.h"

SongList::SongList(FileReceiver* receiver,QObject *parent)
    : QAbstractListModel{parent}, m_Receiver{receiver}
{}

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

void SongList::addSong(const Song &song)
{
    beginInsertRows(QModelIndex(), m_Songs.size(), m_Songs.size());
    m_Songs << song;
    endInsertRows();
}

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

void SongList::extractSongsFromFile(const QUrl &file)
{
    Song song;
    OperationResult result{m_Receiver->getSongFromFile(file,song)};

    if(!result.isSuccessful)
    {
        emit errorReceived(result.error);
        return;
    }

    addSong(song);
}
