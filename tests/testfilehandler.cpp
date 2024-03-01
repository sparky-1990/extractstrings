#include <QTest>
#include "../filehandler.h"

class testFileHandler: public QObject
{
    Q_OBJECT

private slots:

    [[maybe_unused]] void runTests();



};


[[maybe_unused]] void testFileHandler::runTests()
{
    FileHandler testHandler;

    //QVariantList list = {"1",2,"3","Column 4"};
    //auto rows = table.addRow(list);
    //QVERIFY2(rows == 1,"addRow did not return the right number of rowCount");
    //rows = table.rows();
    //QVERIFY2(rows == 1,"rowCount did not return the right number of rowCount");
    //auto columns = table.columns() ;
    //QVERIFY2(columns == 4,"columnCount did not  return the correct size");
    //table.addRow(list);
}

#include "testfilehandler.moc"

QTEST_MAIN(testFileHandler)
