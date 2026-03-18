#ifndef FOLDERVALIDATOR_H
#define FOLDERVALIDATOR_H

#include "InputValidator.h"

class SONGIMPORTERLIB_EXPORT FolderValidator : public InputValidator
{
    Q_OBJECT
public:
    explicit FolderValidator(QObject *parent = nullptr);


public slots:
    [[nodiscard]] ValidationResult validate(const QString &input) const override;
};

#endif // FOLDERVALIDATOR_H
