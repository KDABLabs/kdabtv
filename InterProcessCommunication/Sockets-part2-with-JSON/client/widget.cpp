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

#include "widget.h"
#include "ui_widget.h"
#include "connection.h"
#include "person.h"

#include <QDebug>
#include <QProcess>

static const int s_countryColumn = 3;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , m_connection(new Connection(this))
{
    ui->setupUi(this);

    // Run server
    if (true) {
        // For ease of development: let's start the server ourselves
        // In production, you probably have both things running independently
        m_process = new QProcess(this);
        connect(m_process, &QProcess::errorOccurred, this, [this](QProcess::ProcessError error) {
            qWarning() << "Error:" << error;
        });

        m_process->setProcessChannelMode(QProcess::ForwardedChannels);

        const QString binDir = QApplication::applicationDirPath();
#ifdef Q_OS_WIN
        m_process->start(binDir + "/PeopleServer.exe", QStringList());
#else
        m_process->start(binDir + "/PeopleServer", QStringList());
#endif
        const bool ok = m_process->waitForStarted(); // so we can connect to it
        if (ok) {
            qDebug() << "PeopleServer started";
        } // otherwise errorOccured() is emitted
    }

    // Prepare GUI
    connect(ui->runButton, &QPushButton::clicked, this, &Widget::queryPersonMatches);
    ui->runButton->setEnabled(false); // we're not connected yet
    connect(ui->lineEdit, &QLineEdit::returnPressed, this, &Widget::queryPersonMatches);
    const QStringList labels { tr("First Name"), tr("Last Name"), tr("City"), tr("Country") };
    ui->tableWidget->setColumnCount(labels.count());
    ui->tableWidget->setHorizontalHeaderLabels(labels);
    for (int i = 0; i < labels.size(); ++i) {
        // shared with the server
        static const char* s_fieldNames[] = { "firstName", "lastName", "city", "country"};
        ui->comboBox->addItem(labels.at(i), QString::fromLatin1(s_fieldNames[i]));
    }

    connect(m_connection, &Connection::connected, ui->runButton, &QPushButton::setEnabled);
    connect(m_connection, &Connection::matchesFetched, this, &Widget::processMatches);
    connect(m_connection, &Connection::countryFlagFetched, this, &Widget::processCountryFlag);

    // Go!
    m_connection->connectToServer();
}

Widget::~Widget()
{
    if (m_process && m_process->state() == QProcess::Running) {
        m_connection->quitServer();
        m_process->waitForFinished();
    }
    m_connection->disconnectFromServer();
    delete ui;
}

void Widget::queryPersonMatches()
{
    m_connection->queryPersonMatches(ui->comboBox->currentData().toString(), ui->lineEdit->text());

    ui->tableWidget->clearContents();
}

void Widget::processMatches(const std::vector<Person> &matches)
{
    const int numRows = matches.size();
    ui->tableWidget->setRowCount(numRows);
    for (int row = 0; row < numRows; ++row) {
        const Person person = matches[row];
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(person.firstName));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(person.lastName));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(person.city));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(person.country));
    }
}

void Widget::processCountryFlag(const QString &country, const QString &flagName)
{
    const QIcon icon(":/flags/" + flagName);
    // Update flag in the table
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QTableWidgetItem* item = ui->tableWidget->item(row, s_countryColumn);
        const QString countryForRow = item->text();
        if (countryForRow == country) {
            item->setData(Qt::DecorationRole, icon);
        }
    }
}

