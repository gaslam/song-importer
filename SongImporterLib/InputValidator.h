#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include "SongImporterLib_global.h"

#include <QList>
#include <QObject>
#include <qobjectdefs.h>
#include <qsharedpointer.h>


struct SONGIMPORTERLIB_EXPORT ValidationResult
{
    Q_GADGET
    Q_PROPERTY(QString error  MEMBER error)
    Q_PROPERTY(bool isSuccessful  MEMBER isSuccessful)
public:

    QString error{};
    bool isSuccessful{false};
};
Q_DECLARE_METATYPE(ValidationResult)




class SONGIMPORTERLIB_EXPORT InputValidator : public QObject
{
    Q_OBJECT
public:
    InputValidator(QObject* parent = nullptr);
public slots:
    [[nodiscard]] virtual ValidationResult validate(const QString& input) const = 0;
};

#endif // INPUTVALIDATOR_H
