#include "FileValidator.h"

#include <QFileInfo>

FileValidator::FileValidator(QObject *parent)
    : InputValidator{parent}
{}

ValidationResult FileValidator::validate(const QString &input) const
{
    QFileInfo fileInfo{input};
    ValidationResult result{};

    if(!fileInfo.exists())
    {
        const QString errorMessage { "file does not exist!! Enter or import a file!!"};
        return failResult(errorMessage, result);
    }


    if(!fileInfo.isFile())
    {
        const QString errorMessage { "Input is not a file!! Enter or import a valid file!!"};
        return failResult(errorMessage, result);
    }

    if(!fileInfo.isReadable())
    {
        const QString errorMessage { "file is not readable!! Enter or import new file!!"};
        return failResult(errorMessage, result);
    }

    const QString suffix{fileInfo.suffix().toLower()};
    if(!m_SupportedFileTypes.isEmpty() && !m_SupportedFileTypes.contains(suffix))
    {
        const QString errorMessage {QString("file type is not supported!! Enter or import new file of the following types: %1!!")
                                       .arg(m_SupportedFileTypes.join(", "))};
        return failResult(errorMessage, result);
    }
        result.isSuccessful = true;
    return result;
}

QStringList FileValidator::supportedFileTypes() const
{
    return m_SupportedFileTypes;
}

void FileValidator::setSupportedFileTypes(const QStringList &newSupportedFileTypes)
{
    if (m_SupportedFileTypes == newSupportedFileTypes)
        return;
    m_SupportedFileTypes = newSupportedFileTypes;
}
