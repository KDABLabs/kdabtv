#include "DoNotShowAgainMessageBox.h"
#include <QApplication>
#include <QDebug>
#include <QHBoxLayout>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto top = new QWidget;
    top->setAttribute(Qt::WA_DeleteOnClose);
    auto layout = new QHBoxLayout(top);

    auto button = new QPushButton("Show Dialog 1");
    layout->addWidget(button);
    QObject::connect(button, &QPushButton::clicked, [] {
        auto result = DoNotShowAgainMesageBox::information("MyKey", nullptr, "Hello World",
                                                           "Continue Watching QWAM?",
                                                           QMessageBox::Ok | QMessageBox::Cancel);
        qDebug() << result;
    });

    button = new QPushButton("Show Dialog 2");
    layout->addWidget(button);
    QObject::connect(button, &QPushButton::clicked, [] {
        auto result = DoNotShowAgainMesageBox::information(
            "MyOtherKey", nullptr, "Hello World (yet again)", "Yet another question",
            QMessageBox::Ok | QMessageBox::Cancel);
        qDebug() << result;
    });

    button = new QPushButton("Clear Do not Show Again");
    layout->addWidget(button);
    QObject::connect(button, &QPushButton::clicked, [] { DoNotShowAgainMesageBox::clearAll(); });

    button = new QPushButton("Quit");
    layout->addWidget(button);
    QObject::connect(button, &QPushButton::clicked, [] { QApplication::quit(); });

    top->show();

    return a.exec();
}
