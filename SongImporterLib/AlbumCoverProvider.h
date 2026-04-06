#ifndef ALBUMCOVERPROVIDER_H
#define ALBUMCOVERPROVIDER_H

#include "SongImporterLib_global.h"
#include <QQuickImageProvider>
#include <QMutex>

class SONGIMPORTERLIB_EXPORT AlbumCoverProvider : public QQuickImageProvider
{

public:

    AlbumCoverProvider();

    void setDefaults(const QString& defaultId, const QImage& defaultImage);
    void addImage(const QString &id, const QImage& image);
    [[nodiscard]] bool hasImage(const QString& id) const;

    static AlbumCoverProvider *m_Instance;


public:
    static AlbumCoverProvider* Instance();

private:
    QString m_DefaultId;
    QHash<QString,QImage> m_Images;
    QMutex m_Mutex;

    // QQuickImageProvider interface
public:
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;


    Q_DISABLE_COPY(AlbumCoverProvider)
};

#endif // ALBUMCOVERPROVIDER_H
