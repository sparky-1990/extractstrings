#include "runoptions.h"

#include <QCommandLineParser>
#include <iostream>

RunOptions::RunOptions() {
}

RunOptions::~RunOptions()
{

    if (headerStream != nullptr) delete headerStream;
    if (header != nullptr) delete header;

    if (translationStream != nullptr) delete translationStream;
    if (translationStream != nullptr) delete translation;
}


int RunOptions::ParseCommandLine(QCoreApplication& app)
{

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

    inputFile = parser.value(inputFileOption);
    headerFile = parser.value(headerFileOption);
    translationFile = parser.value(translationFileOption);
    appendOutput = parser.isSet(appendOutputOption);
    silentMode = parser.isSet(silentModeOption);
    verboseMode = parser.isSet(verboseModeOption);

    if (inputFile.isEmpty()) {
        std::cerr << "Input file unspecified." << std::endl;
        return -1;
    }

    if (headerFile.isEmpty() && translationFile.isEmpty()) {
        if (!silentMode)
        {
            std::cout << "No output file found." << std::endl;
            return -2;
        }
    }

    return 0;
}
