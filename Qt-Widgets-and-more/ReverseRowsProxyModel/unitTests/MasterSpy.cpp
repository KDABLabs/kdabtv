#include "MasterSpy.h"
#include "EnumHelper.h"
#include <QAbstractItemModel>
#include <QDebug>
#include <QSignalSpy>
#include <QVariant>

MasterSpy::MasterSpy(QAbstractItemModel *model)
{
    qRegisterMetaType<Qt::Orientation>("Orientation");
    qRegisterMetaType<QList<QPersistentModelIndex>>("QList<QPersistentModelIndex>");
    qRegisterMetaType<QAbstractItemModel::LayoutChangeHint>("LayoutChangeHint");

#define ADD(which) m_signals.insert(which, new QSignalSpy(model, &QAbstractItemModel::which))
    ADD(columnsAboutToBeInserted);
    ADD(columnsAboutToBeMoved);
    ADD(columnsAboutToBeRemoved);
    ADD(columnsInserted);
    ADD(columnsMoved);
    ADD(columnsRemoved);
    ADD(rowsAboutToBeInserted);
    ADD(rowsAboutToBeMoved);
    ADD(rowsAboutToBeRemoved);
    ADD(rowsInserted);
    ADD(rowsMoved);
    ADD(rowsRemoved);
    ADD(dataChanged);
    ADD(headerDataChanged);
    ADD(layoutAboutToBeChanged);
    ADD(layoutChanged);
    ADD(modelAboutToBeReset);
    ADD(modelReset);
}

MasterSpy::~MasterSpy()
{
    qDeleteAll(m_signals);
}

bool MasterSpy::verifyMultipleEmissions(const QList<SignalEmission> &emissions)
{
    for (const SignalEmission &emission : emissions) {
        bool ok = verify(emission.whichSignal, emission.parameters);
        if (!ok)
            return false;
    }

    return verifyNoMoreSignals();
}

bool MasterSpy::verifySingleEmission(WhichSignal whichSignal, const QList<QVariant> &changes)
{
    return verify(whichSignal, changes) && verifyNoMoreSignals();
}

bool MasterSpy::verify(MasterSpy::WhichSignal whichSignal, const QList<QVariant> &expected)
{
    Q_ASSERT(m_signals.contains(whichSignal));
    auto spy = m_signals.value(whichSignal);
    if (spy->count() == 0) {
        qWarning() << "No more signal emissions found for" << EnumHelper::toString(whichSignal);
        return false;
    }
    auto actual = spy->takeFirst();
    if (actual.count() < expected.count()) {
        qWarning() << "More arguments expected than emitted";
        qWarning() << "Actual values: " << actual;
        qWarning() << "Expected values: " << expected;
        return false;
    }

    for (int i = 0; i < expected.count(); ++i) {
        if (actual.at(i) != expected.at(i)) {
            qWarning() << i << "th argument didn't match expected value";
            qWarning() << "Actual value  " << actual.at(i);
            qWarning() << "Expected value" << expected.at(i);
            return false;
        }
    }
    return true;
}

bool MasterSpy::verifyNoMoreSignals()
{
    for (auto it = m_signals.cbegin(); it != m_signals.cend(); ++it) {
        if (it.value()->count() != 0) {
            qWarning() << "There were undetected signals by" << EnumHelper::toString(it.key());
            return false;
        }
    }
    return true;
}
