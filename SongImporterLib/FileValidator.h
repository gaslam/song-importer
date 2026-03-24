#ifndef FILEVALIDATOR_H
#define FILEVALIDATOR_H

#include "InputValidator.h"

class SONGIMPORTERLIB_EXPORT FileValidator : public InputValidator
{
    Q_OBJECT
public:
    explicit FileValidator(QObject *parent = nullptr);

    QStringList supportedFileTypes() const;
    void setSupportedFileTypes(const QStringList &newSupportedFileTypes);

public slots:
    [[nodiscard]] OperationResult validate(const QString &input) const override;

private:
    QStringList m_SupportedFileTypes;
    Q_PROPERTY(QStringList supportedFileTypes READ supportedFileTypes WRITE setSupportedFileTypes FINAL)
};

#endif // FILEVALIDATOR_H
