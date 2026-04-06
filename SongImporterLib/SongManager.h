#ifndef SONGMANAGER_H
#define SONGMANAGER_H

#include "FileReceiver.h"
#include <QObject>
#include <QThread>
#include <qeventloop.h>

class SongManager : public QObject
{
    Q_OBJECT
public:
    explicit SongManager(QObject *parent = nullptr);

    ~SongManager();

    void addSong(const QString& file);

signals:
    void start();
    void stop();
    void songReceived(const Song& song);

public slots:
    void quit();

private slots:
    void process(const QString& file);
    void songProcessed(const Song& song);

    static void createWorker(SongManager* manager,const QString& file);
};

#endif // SONGMANAGER_H
