#include <QString>
#include <QtTest>

class GameEventHandlerTest : public QObject
{
    Q_OBJECT

public:
    GameEventHandlerTest();

private Q_SLOTS:
    void testCase1();
};

GameEventHandlerTest::GameEventHandlerTest()
{
}

void GameEventHandlerTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(GameEventHandlerTest)

#include "tst_gameeventhandlertest.moc"
