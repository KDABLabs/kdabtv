/* MIT License

Copyright (C) 2021 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

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

#include "QWAMPluginCollection.h"
#include "DateSelectorButton.h"
#include "FileSelector.h"
#include "QWAMPlugin.h"
#include <QMessageBox>

static QtMessageHandler original_handler;

// On windows we will not see stdout and stderr from designer and creator, so in case of errors
// better bring up a message box.
void QWAMMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    if (type == QtCriticalMsg || type == QtFatalMsg) {

        QMessageBox::information(nullptr, "Message From KDV",
                                 QString("A qFatal or a qCritical was executed in file: %1 line "
                                         "%2, function: %3, message: \"%4\"")
                                     .arg(context.file)
                                     .arg(context.line)
                                     .arg(context.function)
                                     .arg(msg));
        if (type == QtFatalMsg)
            std::abort();
    } else
        original_handler(type, context, msg);
}

QWAMPluginCollection::QWAMPluginCollection(QObject *parent)
    : QObject(parent)
{
    original_handler = qInstallMessageHandler(QWAMMessageHandler);

#define addPlugin(section, name)                                                                   \
    new QWAMPlugin(section, #name, #name ".h", [](QWidget *parent) { return new name(parent); })

    m_collection = {addPlugin("Qt Widgets and More", DateSelectorButton),
                    addPlugin("Qt Widgets and More", FileSelector)};
}

QList<QDesignerCustomWidgetInterface *> QWAMPluginCollection::customWidgets() const
{
    return m_collection;
}
