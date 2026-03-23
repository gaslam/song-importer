#ifndef FILEUTILS_H
#define FILEUTILS_H

#include "SongImporterLib_global.h"

#include <QObject>
#include <QStandardPaths>
#include <QUrl>
#include <QDir>


class SONGIMPORTERLIB_EXPORT FileUtils : public QObject {
    Q_OBJECT

    // Enum for supported software
    enum SupportedSoftware {
        Rekordbox,
        // add more as needed
    };
    Q_ENUM(SupportedSoftware)

public:
    explicit FileUtils(QObject* parent = nullptr) : QObject{parent}
        {
        }
public slots:
    [[nodiscard]] inline static QString localPath(const QUrl &input) {
        return input.toLocalFile();
    }

    [[nodiscard]] inline static QString musicFolder()
    {
        return QStandardPaths::writableLocation(QStandardPaths::MusicLocation);
    }

    [[nodiscard]] inline static QString softwareDataLocation(const SupportedSoftware& software)
    {
        QDir installDir{QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)};

        installDir = installDir.path();

        switch(software)
        {

        case Rekordbox:
            installDir = installDir.filePath("rekordbox/rekordbox/rekordbox.xml");
            break;
        }

        return installDir.absolutePath();
    }
};

#endif // FILEUTILS_H
