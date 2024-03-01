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

    QFile* header = nullptr;
    QTextStream* headerStream = nullptr;

    QTextStream* translationStream = nullptr;
    QFile* translation = nullptr;

    int ParseCommandLine(QCoreApplication& app);

};

#endif // RUNOPTIONS_H
