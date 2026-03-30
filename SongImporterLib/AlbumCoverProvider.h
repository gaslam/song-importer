#ifndef ALBUMCOVERPROVIDER_H
#define ALBUMCOVERPROVIDER_H

#include "SongImporterLib_global.h"
#include <QQuickImageProvider>

class SONGIMPORTERLIB_EXPORT AlbumCoverProvider : public QQuickImageProvider
{
public:
    AlbumCoverProvider(const QString& defaultId, const QImage& defaultImage);


public:
    void addImage(const QString &id, const QImage& image);
    [[nodiscard]] bool hasImage(const QString& id) const;

private:
    const QString m_DefaultId;
    QHash<QString,QImage> m_Images;

    // QQuickImageProvider interface
public:
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
};

#endif // ALBUMCOVERPROVIDER_H
