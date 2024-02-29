#include "filehandler.h"
#include <QFile>
#include <QTextStream>
#include <QCommandLineParser>
#include <iostream>
FileHandler::FileHandler(QObject *parent)
    : QObject{parent}
{}

void FileHandler::rcFile(RunOptions& myRunOptions, Statistics& myRunStats)
{
    QFile input(myRunOptions.inputFile);
    QTextStream inputStream(&input);

    if (!input.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Cannot open input file." << std::endl;
        return;
    }


    myRunOptions.header = new QFile(myRunOptions.headerFile);
    myRunOptions.headerStream = new QTextStream(myRunOptions.header);

    if (!myRunOptions.header->open(myRunOptions.appendOutput ? QIODevice::Append | QIODevice::Text : QIODevice::WriteOnly | QIODevice::Text))
    {
        std::cerr << "Cannot open or create header file." << std::endl;
        input.close();
        return;
    }


    myRunOptions.translation = new QFile(myRunOptions.translationFile);
    myRunOptions.translationStream = new QTextStream(myRunOptions.translation);

    if (!myRunOptions.translation->open(myRunOptions.appendOutput ? QIODevice::Append | QIODevice::Text : QIODevice::WriteOnly | QIODevice::Text))
    {
        std::cerr << "Cannot open or create translation file." << std::endl;
        input.close();
        myRunOptions.header->close();
        return;
    }


    while (!inputStream.atEnd()) {
        QString line = inputStream.readLine().trimmed();

        if (line.startsWith("STRINGTABLE")) {
            if (myRunOptions.verboseMode)
                std::cout << "STRINGTABLE" << std::endl;

            line = inputStream.readLine().trimmed();
            if (line == "BEGIN") {
                myRunStats.tables++;
                while (!inputStream.atEnd()) {
                    line = inputStream.readLine().trimmed();
                    if (line == "END") {
                        if (myRunOptions.verboseMode)
                            std::cout << "END" << std::endl;
                        break;
                    }

                    handleLine(line, myRunOptions, myRunStats);

                }
            }

        }

        input.close();
        myRunOptions.header->close();
        myRunOptions.translation->close();

    }
}

/*
 * Example String Table
 *
 *
STRINGTABLE DISCARDABLE
BEGIN
    IDS_MUSTBE_POSITIVE     "Item numbers must be between 1 and Count"
    IDS_BEYOND_COUNT        "Requested item is beyond the count of Items."
    IDS_NOROW               "Invalid Row number specificed"
    IDS_OUTOFDEF            "Invalid dimension specified"
    IDS_OUTOFBOUNDS         "Requested cell is out of the current boundries of the table."
    IDS_MUST_ONE            "The dimension must be least one "
    IDS_CANNT_EXTEND        "The new cells cannt be added. Run out of memory"
    IDS_NOT_SUPPORT         "The object not supported"
    IDS_NO_NAME             "The cell has no name asociated"
    IDS_NO_MEM              "There is no memmory to be allocated"
    IDS_OUTOFMEMORY         "Out of Memory"
END

  */


void FileHandler::handleLine(QString line, RunOptions& myRunOptions, Statistics& myRunStats )
{
    // Line is already trimmed

    // Find the Identifier and the String


    // To find the identifier we need to break the line in half based in white space in the middle
    myRunStats.strings++;

    QString identifier;
    QString text;

    int firstSpace  = line.indexOf(" ");
    identifier = line.first(firstSpace).toLower();

    text = line.mid(firstSpace).trimmed();


    identifier.replace('_', '-');

    if (identifier.startsWith("ids")) {
        identifier.replace(0, 2, "str-id");
    }
    else
    {
        //If started with id and some x
        // e.g.   id1 = str_id_1, idq = str_id_q

        if (identifier.startsWith("id")) {
            QString prefix = identifier.first(identifier.indexOf("-"));

            QString newPrefix = "str-id-" + prefix.mid(2);

            identifier.replace(0, prefix.size()-1, newPrefix );
        }
        else
        {
            if (identifier.startsWith("afx")) {
                identifier.replace(0, 2, "str-ido" );
            }
        }

    }

    //Ok we can see what we have!
    //    Note I suspect the text still needs clean up because it will likly have quotes on either end.

    //TODO: Clean up text
    qDebug() << identifier << " = " << text << Qt::endl;
}
//TODO:  Now do something with the line

void FileHandler::handleWriteHeader(QString identifier, QString text, RunOptions& myRunOptions, Statistics& myRunStats)
{
    if (myRunOptions.header && myRunOptions.headerStream)

    {
        // Write to the header file
        *myRunOptions.headerStream << "#define " << identifier << " \"" << text << "\"" << Qt::endl;

        myRunStats.headerWrites++;
    }
}
void FileHandler::handleWriteTranslation(QString identifier, QString text, RunOptions& myRunOptions, Statistics& myRunStats)
{
    if (myRunOptions.translation && myRunOptions.translationStream)

    {
        // Write to the translation file
        *myRunOptions.translationStream << identifier << "=" << text << Qt::endl;

        myRunStats.translationWrites++;
    }


    myRunOptions.header->close();
    myRunOptions.translation->close();
}
