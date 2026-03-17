#include "FolderValidator.h"

#include <QDir>

FolderValidator::FolderValidator(QObject *parent)
    : InputValidator{parent}
{}

ValidationResult FolderValidator::validate(const QString &input) const
{
    ValidationResult result{};

    auto fail = [&result](const QString &message) {
        result.isSuccessful = false;
        result.error = message;
        qCritical() << message;
        return result;
    };

    if(input.isNull() || input.isEmpty())
    {
        return fail("Directory is empty. Enter a valid directory!");
    }

    QDir actualDirectory{input};

    if(!actualDirectory.exists())
    {
        return fail("Directory does not exist. Enter a valid directory!");
    }

    if(!actualDirectory.isReadable() || actualDirectory.isEmpty())
    {
        return fail("Directory is not readable. Enter a valid directory!");
    }

    result.isSuccessful = true;
    return result;
}
