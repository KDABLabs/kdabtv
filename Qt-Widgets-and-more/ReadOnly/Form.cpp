#include "Form.h"
#include "ui_Form.h"
#include <DepecheModel.h>
#include <QDesktopServices>
#include <QListView>
#include <QTableView>
#include <QTreeView>

Form::Form(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Form)
{
    ui->setupUi(this);
    auto model = new DepecheModel;
    ui->listView->setModel(model);
    ui->tableView->setModel(model);
    ui->treeView->setModel(model);
    ui->lineEdit->setText("Hello from the QWAM world");

    QString str;
    for (int i = 0; i < 100; ++i) {
        str += QString("Hello World %1\n").arg(i);
    }
    ui->plainTextEdit->setPlainText(str);
    ui->textEdit->setText(str);

    ui->dateEdit->setCalendarPopup(true);
    ui->dateTimeEdit->setCalendarPopup(true);

    connect(ui->setMyText, &QPushButton::clicked,
            [this] { ui->setMyText->setText("Ohhh this changed the value!"); });

    ui->url->setText("https://www.youtube.com/playlist?list=PL6CJYn40gN6gf-G-o6syFwGrtq3kItEqI");
    connect(ui->openURL, &QPushButton::clicked, this,
            [this] { QDesktopServices::openUrl(ui->url->text()); });
}

Form::~Form()
{
    delete ui;
}
