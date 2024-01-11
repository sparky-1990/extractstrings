#ifndef RUNOPTIONS_H
#define RUNOPTIONS_H
#include <QString>
#include <QFile>
#include <QTextStream>
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
};

#endif // RUNOPTIONS_H
