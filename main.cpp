#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QCommandLineParser>
#include "filehandler.h"
#include <iostream>
#include "statistics.h"
#include "runoptions.h"


//process the RC file and extract strings

int main(int argc, char *argv[]) {
    Statistics myRunStats;
    RunOptions myRunOptions;

    QCoreApplication app(argc, argv);

    QCoreApplication::setApplicationName("extractstrings");

    int isCommandLineOK = myRunOptions.ParseCommandLine(app);
    if (isCommandLineOK<0)
    {
        return isCommandLineOK;
    }

    FileHandler myHandler;

    myHandler.rcFile(myRunOptions, myRunStats) ;

    return 0;
}
