#ifndef RUNOPTIONS_H
#define RUNOPTIONS_H
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>

class RunOptions
{
public:
    RunOptions();
    ~RunOptions();


    QString inputFile;
    QString headerFile;
    QString translationFile;
    bool appendOutput;
    bool silentMode;
    bool verboseMode;

    QFile* header;
    QTextStream* headerStream;

    QTextStream* translationStream;
    QFile* translation;

    int ParseCommandLine(QCoreApplication& app);

};

#endif // RUNOPTIONS_H
