#include "FolderValidator.h"

#include <QDir>

FolderValidator::FolderValidator(QObject *parent)
    : InputValidator{parent}
{}

OperationResult FolderValidator::validate(const QString &input) const
{
    OperationResult result{};

    if(input.isNull() || input.isEmpty())
    {
        return failResult("Directory is empty. Enter a valid directory!",result);
    }

    QDir actualDirectory{input};

    if(!actualDirectory.exists())
    {
        return failResult("Directory does not exist. Enter a valid directory!",result);
    }

    if(!actualDirectory.isReadable() || actualDirectory.isEmpty())
    {
        return failResult("Directory is not readable. Enter a valid directory!",result);
    }

    result.isSuccessful = true;
    return result;
}
