#include "InputValidator.h"
#include <QDebug>

InputValidator::InputValidator(QObject *parent): QObject{parent}
{

}

OperationResult InputValidator::failResult(const QString &message,OperationResult& result) const
{
    result.isSuccessful = false;
    result.error = message;
    qCritical() << message;
    return result;
}
