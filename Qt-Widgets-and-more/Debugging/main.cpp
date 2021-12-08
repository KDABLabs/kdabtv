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

#include "Money.h"
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QLoggingCategory>
#include <QMessageBox>
#include <QPushButton>

Q_LOGGING_CATEGORY(GeneralLog, "QWAM.General")

namespace {
static QtMessageHandler qwam_original_handler;

void QWAMMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    if (type == QtCriticalMsg || type == QtFatalMsg) {

        QMessageBox::information(nullptr, "Message From QWAM",
                                 QString("A qFatal or a qCritical was executed in file: %1 line "
                                         "%2, function: %3, message: \"%4\"")
                                     .arg(context.file)
                                     .arg(context.line)
                                     .arg(context.function)
                                     .arg(msg));
        if (type == QtFatalMsg)
            std::abort();
    } else
        qwam_original_handler(type, context, msg);
}

}

void basicUsage()
{
    // qSetMessagePattern("%{function}(%{type}) %{message}");

    QString aString = "Hello world";

    qDebug("Hello world: %s %d", qPrintable(aString), 42);
    qDebug() << "Hello world" << aString << 42;

    qWarning() << "Let me warn you!";
    qInfo() << "Just FYI!";
    qCritical() << "The end is near!";

    qFatal("OK here it is!");
    qDebug() << "We indeed died in the qFatal line";
}

void missingQFatal()
{
#define myFatal() QDebug(QtFatalMsg)
    myFatal() << "Ohhh"
              << "Bugger";
}

void printingOwnTypes()
{
    Money amount(Currency::EUR, 100);
    Money invalid;

    qDebug() << "Jesper has:" << amount << "You get: " << invalid;
}

void formattingToAString()
{
    Money amount(Currency::EUR, 100);

    QString string;
    QDebug printer(&string);

    printer << "Jesper has";
    printer << amount << "Which is €" << Qt::hex << Qt::showbase << 100 << "in hexadecimal euros."
            << Qt::endl;

    qDebug() << string;
}

void streamingToAFile()
{
    // Obviously I could implement QTextStream<< for the money class, but if I already have it
    // implemented for QDebug then this might be easier.
    Money amount(Currency::EUR, 100);

    QFile output("/tmp/dummy.txt");
    output.open(QIODevice::WriteOnly);

    QDebug(&output) << "Jesper has" << amount;
}

void messageHandlers()
{
    Money amount(Currency::EUR, 100);
    Money invalid;

    qwam_original_handler = qInstallMessageHandler(QWAMMessageHandler);

    qDebug() << "Jesper has:" << amount;
    qWarning() << "You get: " << invalid;
    qInfo() << "Just FYI!";
    qCritical() << "The end is near!";
    qFatal("OK here it is!");
    qDebug() << "We indeed died in the qFatal line";
}

void loggingCategories()
{
    auto button = new QPushButton("Go");
    button->show();
    QObject::connect(button, &QPushButton::clicked, [] {
        Money amount(Currency::EUR, 100);
        qCDebug(GeneralLog) << amount;
    });
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    basicUsage();
    missingQFatal();
    printingOwnTypes();
    formattingToAString();
    streamingToAFile();
    messageHandlers();
    loggingCategories();

    app.exec();
}
