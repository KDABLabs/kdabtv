/* MIT License

Copyright (C) 2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "ModelTesting.h"
#include <QAbstractItemModelTester>
#include <QCoreApplication>
#include <QDebug>
#include <private/qhooks_p.h>

namespace {
void (*qwam_next_addObject)(QObject *) = nullptr;
int ItsAliveType = 0;
constexpr const char DONOTTESTMODEL[] = "QWAM_DO_NOT_TEST_MODEL";

void qwam_addObject(QObject *obj)
{
    // At the time when the object comes alive it has only been constructed to the QObject level,
    // which is too early for us to check if it is a model. So post an event to it. At the time it
    // receives the event it will have been fully constructed.
    QCoreApplication::postEvent(obj, new QEvent((QEvent::Type)ItsAliveType));

    if (qwam_next_addObject)
        qwam_next_addObject(obj);
}
}

ModelTesting::ModelTesting()
{
    // Only attached to the models if this environment variable is set
    if (qEnvironmentVariableIsEmpty("QWAM_TEST_MODELS"))
        return;

    qDebug("Turning on QAbstractItemModelTester on all objects.");

    Q_ASSERT(ItsAliveType == 0); // We don't support setting this up multiple times.
    ItsAliveType = QEvent::registerEventType();

    qwam_next_addObject =
        reinterpret_cast<QHooks::AddQObjectCallback>(qtHookData[QHooks::AddQObject]);
    qtHookData[QHooks::AddQObject] = reinterpret_cast<quintptr>(&qwam_addObject);

    qApp->installEventFilter(this);
}

bool ModelTesting::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() != ItsAliveType)
        return QObject::eventFilter(watched, event);

    // Observe, as we know it is our own type, the remaining returns are always true, as we do not
    // want to show this event to the object itself.

    if (qtHookData[QHooks::AddQObject] != reinterpret_cast<quintptr>(&qwam_addObject)) {
        // Something got ahead of us in the hooks, very likely GammaRay.
        // Let's leave it to the GammaRay team to get their models 100% compatible with the model
        // tester.
        return true;
    }

    if (auto model = qobject_cast<QAbstractItemModel *>(watched)) {
        // QCalendarModel is broken in 5.15 and below, so ignore it.
        // It is an internal class in Qt anyway, so not possible to subclass from user code.
        if (model->property(DONOTTESTMODEL).isValid() || model->inherits("QCalendarModel")
            || model->inherits("QCompletionModel")) {
            return true;
        }

        // You likely want to remove this from your own code.
        qDebug() << "Testing class " << watched->metaObject()->className();
        new QAbstractItemModelTester(model, QAbstractItemModelTester::FailureReportingMode::Warning,
                                     model);
    }
    return true;
}

void ModelTesting::ignoreModel(QAbstractItemModel *model)
{
    model->setProperty(DONOTTESTMODEL, true);
}
