#include <QString>
#include <QtTest>
//#include "objectmanager.hh"

class ObjectManagerTest : public QObject
{
    Q_OBJECT

public:
    ObjectManagerTest();

private Q_SLOTS:
    void testCase1();
};

ObjectManagerTest::ObjectManagerTest()
{
}

void ObjectManagerTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(ObjectManagerTest)

#include "tst_objectmanagertest.moc"
