#include "../ReverseRowsProxyModel.h"
#include "MasterSpy.h"
#include <QCoreApplication>
#include <QModelIndex>
#include <QPersistentModelIndex>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QTest>

class ReverseRowsProxyModelTest : public QObject
{
    Q_OBJECT

public:
    using QObject::QObject;

private slots:
    void staticMethods();

    void dataChanged();
    void dataChanged_data();

    void dataChangedRange();

    void rowsAdded();
    void rowsAdded_data();

    void rowsRemoved();
    void rowsRemoved_data();

    void columnsAdded();
    void columnsAdded_data();

    void columnsRemoved();
    void columnsRemoved_data();

    void moveRows();
    void moveRows_data();

    void headerDataChanged();
    void headerDataChanged_data();

    void layoutChanged();

private:
    void setup();
    void basicChecks();

    const int rows = 8;
    const int columns = 6;
    QStandardItemModel *model = nullptr;
    ReverseRowsProxyModel *proxy = nullptr;
    MasterSpy *modelSpy = nullptr;
    MasterSpy *proxySpy = nullptr;
};

void ReverseRowsProxyModelTest::setup()
{
    delete modelSpy;
    delete model;
    delete proxySpy;
    delete proxy;

    model = new QStandardItemModel(rows, columns);
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            model->setItem(row, col, new QStandardItem(QString("(%1,%2)").arg(row).arg(col)));
        }
    }

    proxy = new ReverseRowsProxyModel;
    proxy->setSourceModel(model);

    modelSpy = new MasterSpy(model);
    proxySpy = new MasterSpy(proxy);
}

void ReverseRowsProxyModelTest::basicChecks()
{
    QCOMPARE(proxy->rowCount(), model->rowCount());
    QCOMPARE(proxy->columnCount(), model->columnCount());

    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QCOMPARE(proxy->index(model->rowCount() - row - 1, col).data().toString(),
                     model->index(row, col).data().toString());
        }
    }
}

void ReverseRowsProxyModelTest::staticMethods()
{
    setup();
    QCOMPARE(proxy->rowCount(), rows);
    QCOMPARE(proxy->columnCount(), columns);
    QCOMPARE(proxy->index(0, 0).data().toString(), QString("(7,0)"));
    QCOMPARE(proxy->index(7, 0).data().toString(), QString("(0,0)"));
    QCOMPARE(proxy->index(0, 4).data().toString(), QString("(7,4)"));
    QCOMPARE(proxy->index(7, 4).data().toString(), QString("(0,4)"));
}

void ReverseRowsProxyModelTest::dataChanged()
{
    QFETCH(QString, text);
    QFETCH(int, srcRow);
    QFETCH(int, destRow);
    QFETCH(int, column);

    setup();

    model->item(srcRow, column)->setText(text);
    QCOMPARE(model->index(srcRow, column).data().toString(), QString(text));
    QCOMPARE(proxy->index(destRow, column).data().toString(), QString(text));

    QVERIFY(modelSpy->verifySingleEmission(
        MasterSpy::dataChanged, {model->index(srcRow, column), model->index(srcRow, column)}));

    QVERIFY(proxySpy->verifySingleEmission(
        MasterSpy::dataChanged, {proxy->index(destRow, column), proxy->index(destRow, column)}));
}

void ReverseRowsProxyModelTest::dataChanged_data()
{
    QTest::addColumn<QString>("text");
    QTest::addColumn<int>("srcRow");
    QTest::addColumn<int>("destRow");
    QTest::addColumn<int>("column");

    QTest::newRow("At the beginning") << "Hello" << 0 << 7 << 0;
    QTest::newRow("In The middle") << "World" << 7 << 0 << 1;
    QTest::newRow("At the end") << "FooBar" << 1 << 6 << 2;
}

void ReverseRowsProxyModelTest::dataChangedRange()
{
    setup();

    emit model->dataChanged(model->index(0, 2), model->index(2, 4));
    QVERIFY(proxySpy->verifySingleEmission(MasterSpy::dataChanged,
                                           {proxy->index(5, 2), proxy->index(7, 4)}));
}

void ReverseRowsProxyModelTest::rowsAdded()
{
    QFETCH(int, srcStart);
    QFETCH(int, srcEnd);
    QFETCH(int, dstStart);
    QFETCH(int, dstEnd);

    setup();
    model->insertRows(srcStart, srcEnd - srcStart + 1, {});
    basicChecks();

    QCOMPARE(model->index(0, 3).data().toString(),
             proxy->index(proxy->rowCount() - 1, 3).data().toString());
    QCOMPARE(model->index(model->rowCount() - 1, 2).data().toString(),
             proxy->index(0, 2).data().toString());

    QVERIFY(modelSpy->verifyMultipleEmissions(
        {{MasterSpy::rowsAboutToBeInserted, {QModelIndex(), srcStart, srcEnd}},
         {MasterSpy::rowsInserted, {QModelIndex(), srcStart, srcEnd}}}));

    QVERIFY(proxySpy->verifyMultipleEmissions(
        {{MasterSpy::rowsAboutToBeInserted, {QModelIndex(), dstStart, dstEnd}},
         {MasterSpy::rowsInserted, {QModelIndex(), dstStart, dstEnd}}}));
}

void ReverseRowsProxyModelTest::rowsAdded_data()
{
    QTest::addColumn<int>("srcStart");
    QTest::addColumn<int>("srcEnd");
    QTest::addColumn<int>("dstStart");
    QTest::addColumn<int>("dstEnd");

    QTest::newRow("one row at the front") << 0 << 0 << 8 << 8;
    QTest::newRow("two rows at the front") << 0 << 1 << 8 << 9;
    QTest::newRow("three rows in the middle") << 1 << 3 << 7 << 9;
    QTest::newRow("two rows at the end") << 8 << 9 << 0 << 1;
}

void ReverseRowsProxyModelTest::rowsRemoved()
{
    QFETCH(int, srcStart);
    QFETCH(int, srcEnd);
    QFETCH(int, dstStart);
    QFETCH(int, dstEnd);

    setup();
    model->removeRows(srcStart, srcEnd - srcStart + 1, {});
    basicChecks();

    QCOMPARE(model->index(0, 3).data().toString(),
             proxy->index(proxy->rowCount() - 1, 3).data().toString());
    QCOMPARE(model->index(model->rowCount() - 1, 2).data().toString(),
             proxy->index(0, 2).data().toString());

    QVERIFY(modelSpy->verifyMultipleEmissions(
        {{MasterSpy::rowsAboutToBeRemoved, {QModelIndex(), srcStart, srcEnd}},
         {MasterSpy::rowsRemoved, {QModelIndex(), srcStart, srcEnd}}}));

    QVERIFY(proxySpy->verifyMultipleEmissions(
        {{MasterSpy::rowsAboutToBeRemoved, {QModelIndex(), dstStart, dstEnd}},
         {MasterSpy::rowsRemoved, {QModelIndex(), dstStart, dstEnd}}}));
}

void ReverseRowsProxyModelTest::rowsRemoved_data()
{
    QTest::addColumn<int>("srcStart");
    QTest::addColumn<int>("srcEnd");
    QTest::addColumn<int>("dstStart");
    QTest::addColumn<int>("dstEnd");

    QTest::newRow("one row at the front") << 0 << 0 << 7 << 7;
    QTest::newRow("two rows at the front") << 0 << 1 << 6 << 7;
    QTest::newRow("three row in the middle") << 1 << 3 << 4 << 6;
    QTest::newRow("two rows at the end") << 6 << 7 << 0 << 1;
}

void ReverseRowsProxyModelTest::columnsAdded()
{
    QFETCH(int, start);
    QFETCH(int, end);

    setup();
    model->insertColumns(start, end - start + 1);
    basicChecks();

    QVERIFY(modelSpy->verifyMultipleEmissions(
        {{MasterSpy::columnsAboutToBeInserted, {QModelIndex(), start, end}},
         {MasterSpy::columnsInserted, {QModelIndex(), start, end}}}));

    QVERIFY(proxySpy->verifyMultipleEmissions(
        {{MasterSpy::columnsAboutToBeInserted, {QModelIndex(), start, end}},
         {MasterSpy::columnsInserted, {QModelIndex(), start, end}}}));
}

void ReverseRowsProxyModelTest::columnsAdded_data()
{
    QTest::addColumn<int>("start");
    QTest::addColumn<int>("end");

    QTest::newRow("one column at the front") << 0 << 0;
    QTest::newRow("two column at the front") << 0 << 1;
    QTest::newRow("a column in the middle") << 2 << 2;
    QTest::newRow("two column at the end") << 5 << 6;
}

void ReverseRowsProxyModelTest::columnsRemoved()
{
    QFETCH(int, start);
    QFETCH(int, end);

    setup();
    model->removeColumns(start, end - start + 1);
    basicChecks();

    QVERIFY(modelSpy->verifyMultipleEmissions(
        {{MasterSpy::columnsAboutToBeRemoved, {QModelIndex(), start, end}},
         {MasterSpy::columnsRemoved, {QModelIndex(), start, end}}}));

    QVERIFY(proxySpy->verifyMultipleEmissions(
        {{MasterSpy::columnsAboutToBeRemoved, {QModelIndex(), start, end}},
         {MasterSpy::columnsRemoved, {QModelIndex(), start, end}}}));
}

void ReverseRowsProxyModelTest::columnsRemoved_data()
{
    QTest::addColumn<int>("start");
    QTest::addColumn<int>("end");

    QTest::newRow("one column at the front") << 0 << 0;
    QTest::newRow("two column at the front") << 0 << 1;
    QTest::newRow("a column in the middle") << 2 << 2;
    QTest::newRow("two column at the end") << 3 << 4;
}

void ReverseRowsProxyModelTest::moveRows()
{
    QFETCH(int, srcStart);
    QFETCH(int, srcEnd);
    QFETCH(int, dest);
    QFETCH(int, mappedSrcStart);
    QFETCH(int, mappedSrcEnd);
    QFETCH(int, mappedDest);

    QStringListModel model(
        {"row 0", "row 1", "row 2", "row 3", "row 4", "row 5", "row 6", "row 7"});
    ReverseRowsProxyModel proxy;
    proxy.setSourceModel(&model);
    MasterSpy myModelSpy(&model);
    MasterSpy myProxySpy(&proxy);

    int count = srcEnd - srcStart + 1;
    model.moveRows({}, srcStart, count, {}, dest);

    QVERIFY(myModelSpy.verifyMultipleEmissions(
        {{MasterSpy::rowsAboutToBeMoved, {QModelIndex(), srcStart, srcEnd, QModelIndex(), dest}},
         {MasterSpy::rowsMoved, {QModelIndex(), srcStart, srcEnd, QModelIndex(), dest}}}));

    QVERIFY(myProxySpy.verifyMultipleEmissions(
        {{MasterSpy::rowsAboutToBeMoved,
          {QModelIndex(), mappedSrcStart, mappedSrcEnd, QModelIndex(), mappedDest}},
         {MasterSpy::rowsMoved,
          {QModelIndex(), mappedSrcStart, mappedSrcEnd, QModelIndex(), mappedDest}}}));
}

void ReverseRowsProxyModelTest::moveRows_data()
{
    QTest::addColumn<int>("srcStart");
    QTest::addColumn<int>("srcEnd");
    QTest::addColumn<int>("dest");
    QTest::addColumn<int>("mappedSrcStart");
    QTest::addColumn<int>("mappedSrcEnd");
    QTest::addColumn<int>("mappedDest");

    QTest::newRow("first row to third row") << 0 << 0 << 2 << 7 << 7 << 5;
    QTest::newRow("last row to third row") << 7 << 7 << 2 << 0 << 0 << 5;
    QTest::newRow("first two rows to third row") << 0 << 1 << 3 << 6 << 7 << 4;
    QTest::newRow("last two rows to third row") << 6 << 7 << 3 << 0 << 1 << 4;

    // OK model doesn't emit any signals for this, so nothing to test
    // QTest::newRow("first row to fist row") << 0 << 0 << 0 << 7 << 7 << 7;
}

void ReverseRowsProxyModelTest::headerDataChanged()
{
    QFETCH(Qt::Orientation, orientation);
    QFETCH(int, from);
    QFETCH(int, to);
    QFETCH(int, mappedFrom);
    QFETCH(int, mappedTo);

    setup();
    emit model->headerDataChanged(orientation, from, to);

    QVERIFY(proxySpy->verifySingleEmission(MasterSpy::headerDataChanged,
                                           {orientation, mappedFrom, mappedTo}));
}

void ReverseRowsProxyModelTest::headerDataChanged_data()
{
    QTest::addColumn<Qt::Orientation>("orientation");
    QTest::addColumn<int>("from");
    QTest::addColumn<int>("to");
    QTest::addColumn<int>("mappedFrom");
    QTest::addColumn<int>("mappedTo");

    QTest::newRow("horizontal first and second element") << Qt::Horizontal << 0 << 1 << 0 << 1;
    QTest::newRow("vertical first and second element") << Qt::Vertical << 0 << 1 << 6 << 7;
}

void ReverseRowsProxyModelTest::layoutChanged()
{
#if 1
    setup();

    std::vector<QPersistentModelIndex> indexes;
    QStringList texts;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            auto proxyIndex = proxy->index(row, col);
            texts.append(proxyIndex.data().toString());
            indexes.push_back(QPersistentModelIndex(proxyIndex));
        }
    }
    model->sort(0, Qt::DescendingOrder);

    for (int i = 0; i < texts.count(); ++i) {
        QCOMPARE(indexes.at(i).data().toString(), texts.at(i));
    }

    basicChecks();

    QVERIFY(
        proxySpy->verifyMultipleEmissions({{MasterSpy::layoutAboutToBeChanged,
                                            {QVariant::fromValue(QList<QPersistentModelIndex>()),
                                             QAbstractItemModel::VerticalSortHint}},
                                           {MasterSpy::layoutChanged,
                                            {QVariant::fromValue(QList<QPersistentModelIndex>()),
                                             QAbstractItemModel::VerticalSortHint}}}));
#endif
}

QTEST_MAIN(ReverseRowsProxyModelTest)

#include "tst_ReverseRowsProxyModel.moc"
