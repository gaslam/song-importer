#include "AlbumCoverProvider.h"

AlbumCoverProvider::AlbumCoverProvider(const QString& defaultId, const QImage& defaultImage)
    : QQuickImageProvider(QQuickImageProvider::Image),
    m_DefaultId{defaultId}
{
    addImage(defaultId,defaultImage);
}

void AlbumCoverProvider::addImage(const QString &id, const QImage &image)
{
    if(!m_Images.contains(id))
    {
        m_Images[id] = image;
    }
}

bool AlbumCoverProvider::hasImage(const QString &id) const
{
    return m_Images.contains(id);
}

QImage AlbumCoverProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    QImage image;
    if(m_Images.contains(id))
    {
        image = m_Images[id];

    }
    else if(m_Images.contains(m_DefaultId))
    {
        image = m_Images[m_DefaultId];
    }

    if(!image.isNull())
    {
        if (size)
            *size = image.size();

        if (requestedSize.width() > 0 && requestedSize.height() > 0)
            image = image.scaled(requestedSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    return image;
}
