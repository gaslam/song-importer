#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include "SongImporterLib_global.h"

#include <QObject>
#include "OperationResult.h"




class SONGIMPORTERLIB_EXPORT InputValidator : public QObject
{
    Q_OBJECT
public:
    InputValidator(QObject* parent = nullptr);
public slots:
    [[nodiscard]] virtual OperationResult validate(const QString& input) const = 0;

protected:
    [[nodiscard]] OperationResult failResult(const QString& input,OperationResult& result) const;
};

#endif // INPUTVALIDATOR_H
