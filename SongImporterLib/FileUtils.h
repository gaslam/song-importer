#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QObject>
#include "SongImporterLib_global.h"
#include <QUrl>


class SONGIMPORTERLIB_EXPORT FileUtils : public QObject {
    Q_OBJECT

public:
    explicit FileUtils(QObject* parent = nullptr) : QObject{parent}
        {

        }
public slots:
    [[nodiscard]] inline static QString localPath(const QUrl &input) {
        return input.toLocalFile();
    }
};

#endif // FILEUTILS_H
