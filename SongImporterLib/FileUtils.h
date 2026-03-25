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
            installDir = installDir.filePath("rekordbox/rekordbox/rekordbox.xml");
            break;
        }

        return installDir.absolutePath();
    }

    [[nodiscard]] inline static OperationResult isZipFile(const QUrl &url)
    {
        QFile f(url.toLocalFile());
        OperationResult result{};
        if (!f.open(QIODevice::ReadOnly))
        {

            result.isSuccessful = false;
            result.error = f.fileName() + "is read-only. Set the permisions to read/write to continue.";
            return result;
        }

        const QByteArray sig = f.read(4);
        if (sig == "PK\x03\x04") // Normal ZIP
        {
            result.isSuccessful = true;
            return result;
        }
        else if (sig == "PK\x05\x06") // empty ZIP
        {
            result.error = "ZIP archive is empty.";
            result.isSuccessful = false;
            return result;
        }
        else if (sig == "PK\x07\x08") //Spanned ZIP
        {
            result.error = "ZIP archive is spanned (multi-part), which is not supported.";
            result.isSuccessful = false;
            return result;
        }

        result.error = "File is not a valid ZIP archive.";
        result.isSuccessful = false;
        return result;

    }
};

#endif // FILEUTILS_H
