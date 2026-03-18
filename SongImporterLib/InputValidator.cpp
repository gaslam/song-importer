#include "InputValidator.h"
#include <QDebug>

InputValidator::InputValidator(QObject *parent): QObject{parent}
{

}

ValidationResult InputValidator::failResult(const QString &message,ValidationResult& result) const
{
    result.isSuccessful = false;
    result.error = message;
    qCritical() << message;
    return result;
}
