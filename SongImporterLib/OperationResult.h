#ifndef OPERATIONRESULT_H
#define OPERATIONRESULT_H

#include "SongImporterLib_global.h"

#include <qobjectdefs.h>
#include <qsharedpointer.h>

struct SONGIMPORTERLIB_EXPORT OperationResult
{
    Q_GADGET
    Q_PROPERTY(QString error  MEMBER error)
    Q_PROPERTY(bool isSuccessful  MEMBER isSuccessful)
public:

    QString error{};
    bool isSuccessful{false};
};
Q_DECLARE_METATYPE(OperationResult)

#endif // OPERATIONRESULT_H
