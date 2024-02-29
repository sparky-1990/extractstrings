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

    QCommandLineParser parser;
    parser.setApplicationDescription("Extract Strings from an RC file");
    parser.addHelpOption();


    QCommandLineOption inputFileOption(QStringList() << "i" << "input", "Input file name", "filename");
    parser.addOption(inputFileOption);

    QCommandLineOption headerFileOption(QStringList() << "header" << "header", "Header file name", "headerfilename");
    parser.addOption(headerFileOption);

    QCommandLineOption translationFileOption(QStringList() << "t" << "translation", "Translation file name", "translationfilename");
    parser.addOption(translationFileOption);

    QCommandLineOption appendOutputOption(QStringList() << "a" << "append", "Append output to target files");
    parser.addOption(appendOutputOption);

    QCommandLineOption silentModeOption(QStringList() << "silent" << "silent", "Run in silent mode");
    parser.addOption(silentModeOption);

    QCommandLineOption verboseModeOption(QStringList() << "verbose" << "verbose", "Run in verbose mode");
    parser.addOption(verboseModeOption);

    parser.process(app);

    myRunOptions.inputFile = parser.value(inputFileOption);
    myRunOptions.headerFile = parser.value(headerFileOption);
    myRunOptions.translationFile = parser.value(translationFileOption);
    myRunOptions.appendOutput = parser.isSet(appendOutputOption);
    myRunOptions.silentMode = parser.isSet(silentModeOption);
    myRunOptions.verboseMode = parser.isSet(verboseModeOption);

    if (myRunOptions.inputFile.isEmpty()) {
        std::cerr << "Input file unspecified." << std::endl;
        return 1;
    }

    if (myRunOptions.headerFile.isEmpty() && myRunOptions.translationFile.isEmpty()) {
        if (!myRunOptions.silentMode)
            std::cout << "No output file found." << std::endl;
    }

    FileHandler myHandler;

    myHandler.rcFile(myRunOptions, myRunStats) ;

    return 0;
}
