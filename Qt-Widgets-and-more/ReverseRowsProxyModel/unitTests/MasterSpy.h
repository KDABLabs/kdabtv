#pragma once

#include <QHash>
#include <QList>
#include <qobjectdefs.h>

class QSignalSpy;
class QAbstractItemModel;
class QVariant;

class MasterSpy
{
    Q_GADGET
public:
    MasterSpy(QAbstractItemModel *model);
    ~MasterSpy();
    MasterSpy(const MasterSpy &other) = delete;
    MasterSpy &operator=(const MasterSpy &other) = delete;

    enum WhichSignal {
        columnsAboutToBeInserted,
        columnsAboutToBeMoved,
        columnsAboutToBeRemoved,
        columnsInserted,
        columnsMoved,
        columnsRemoved,
        rowsAboutToBeInserted,
        rowsAboutToBeMoved,
        rowsAboutToBeRemoved,
        rowsInserted,
        rowsMoved,
        rowsRemoved,
        dataChanged,
        headerDataChanged,
        layoutAboutToBeChanged,
        layoutChanged,
        modelAboutToBeReset,
        modelReset,
    };
    Q_ENUM(WhichSignal);

    struct SignalEmission
    {
        WhichSignal whichSignal;
        QList<QVariant> parameters;
    };

    bool verifyMultipleEmissions(const QList<SignalEmission> &emissions);
    bool verifySingleEmission(WhichSignal whichSignal, const QList<QVariant> &changes);

    bool verify(WhichSignal whichSignal, const QList<QVariant> &changes);
    bool verifyNoMoreSignals();

private:
    QHash<WhichSignal, QSignalSpy *> m_signals;
};
