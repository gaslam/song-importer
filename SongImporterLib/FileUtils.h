#ifndef FILEUTILS_H
#define FILEUTILS_H

#include "SongImporterLib_global.h"

#include <QObject>
#include <QStandardPaths>
#include <QUrl>
#include <QDir>
#include "OperationResult.h"


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
            installDir = installDir.filePath("../rekordbox/rekordbox/rekordbox.xml");
            break;
        }

        return installDir.absolutePath();
    }

    [[nodiscard]] inline static OperationResult isZipFile(const QUrl &url)
    {
        QFile f(url.toLocalFile());
        if (!f.open(QIODevice::ReadOnly))
        {
            const QString error {f.fileName() + "is read-only. Set the permisions to read/write to continue."};
            return OperationResult::fail(error);
        }

        const QByteArray sig = f.read(4);
        if (sig == "PK\x03\x04") // Normal ZIP
        {
            return OperationResult::succeed();
        }
        else if (sig == "PK\x05\x06") // empty ZIP
        {
            const QString error {"ZIP archive is empty."};
            return OperationResult::fail(error);
        }
        else if (sig == "PK\x07\x08") //Spanned ZIP
        {
            const QString error {"ZIP archive is spanned (multi-part), which is not supported."};
            return OperationResult::fail(error);
        }

        const QString error {"File is not a valid ZIP archive."};
        return OperationResult::fail(error);
    }
};

#endif // FILEUTILS_H
