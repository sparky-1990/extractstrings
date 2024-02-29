#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include "statistics.h"
#include "runoptions.h"

class FileHandler : public QObject
{
    Q_OBJECT
public:
    explicit FileHandler(QObject *parent = nullptr);

    void handleLine(QString line,RunOptions& myRunOptions, Statistics& myRunStats);
    void rcFile(RunOptions& myRunOptions, Statistics& myRunStats);

    void handleWriteHeader(QString identifier, QString text,RunOptions& myRunOptions,Statistics& myRunStats);
    void handleWriteTranslation(QString identifier, QString text, RunOptions& myRunOptions, Statistics& myRunStats);

signals:
};

#endif // FILEHANDLER_H
