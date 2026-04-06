#include "AlbumCoverProvider.h"


AlbumCoverProvider* AlbumCoverProvider::m_Instance = nullptr;
AlbumCoverProvider::AlbumCoverProvider()
    : QQuickImageProvider(QQuickImageProvider::Image)
{
}

void AlbumCoverProvider::setDefaults(const QString &defaultId, const QImage &defaultImage)
{
    m_DefaultId = defaultId;
    addImage(defaultId,defaultImage);
}

void AlbumCoverProvider::addImage(const QString &id, const QImage &image)
{
    QMutexLocker<QMutex> locker{&m_Mutex};
    if(!m_Images.contains(id))
    {
        m_Images[id] = image;
    }
}

bool AlbumCoverProvider::hasImage(const QString &id) const
{
    return m_Images.contains(id);
}

AlbumCoverProvider *AlbumCoverProvider::Instance()
{
    if(!m_Instance)
    {
        m_Instance = new AlbumCoverProvider{};
    }

    return m_Instance;
}

QImage AlbumCoverProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    QMutexLocker<QMutex> locker{&m_Mutex};
    QImage image;
    if(m_Images.contains(id))
    {
        image = m_Images[id];

    }
    else if(m_Images.contains(m_DefaultId))
    {
        image = m_Images[m_DefaultId];
    }

    if(image.isNull())
    {
        return image;
    }
    if (size)
        *size = image.size();

    if (!requestedSize.isValid())
        return image;

    image = image.scaled(requestedSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    return image;
}
