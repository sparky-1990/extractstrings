#include <QTest>
#include "../filehandler.h"

class testFileHandler: public QObject
{
    Q_OBJECT

private slots:

    [[maybe_unused]] void runTests();
    void testHandleLine();


};


[[maybe_unused]] void testFileHandler::runTests()
{
    testHandleLine();

    //QVariantList list = {"1",2,"3","Column 4"};
    //auto rows = table.addRow(list);
    //QVERIFY2(rows == 1,"addRow did not return the right number of rowCount");
    //rows = table.rows();
    //QVERIFY2(rows == 1,"rowCount did not return the right number of rowCount");
    //auto columns = table.columns() ;
    //QVERIFY2(columns == 4,"columnCount did not  return the correct size");
    //table.addRow(list);
}

void  testFileHandler::testHandleLine()
{
    FileHandler testHandler;
    RunOptions opts;
    Statistics stats;
    QString line = "IDS_MUSTBE_POSITIVE     \"Item numbers must be between 1 and Count\"";
    testHandler.handleLine(line,opts,stats);
    //QVERIFY2(stats.strings == 1, "Stats not 1");

}
#include "testfilehandler.moc"

QTEST_MAIN(testFileHandler)
