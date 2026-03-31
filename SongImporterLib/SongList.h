#ifndef SONGLIST_H
#define SONGLIST_H

#include <QAbstractListModel>
#include "SongImporterLib_global.h"
#include "FileReceiver.h"

class SONGIMPORTERLIB_EXPORT SongList : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit SongList(FileReceiver* receiver,QObject *parent = nullptr);

    enum ContactRoles {
        TitleRole = Qt::UserRole + 1,
        ArtistsRole,
        YearRole,
        AlbumCoverRole,
        AlbumRole,
        ColumnCount
    };

    int columnCount(const QModelIndex &) const override;

    int rowCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
public slots:
    void extractSongsFromFiles(const QList<QUrl> &files);

signals:
    void errorReceived(const QString& error);
private:
    OperationResult addSongs(const QList<Song> &song);
    OperationResult addSong(const Song& song);

    [[nodiscard]] bool isSongAlreadyInList(const Song& song) const;
    QList<Song> m_Songs;
    FileReceiver* m_Receiver;
};

#endif // SONGLIST_H
