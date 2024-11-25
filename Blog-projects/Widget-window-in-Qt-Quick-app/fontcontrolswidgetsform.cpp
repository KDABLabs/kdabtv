#include "fontcontrolswidgetsform.h"
#include "ui_fontcontrolswidgetsform.h"

FontControlsWidgetsForm::FontControlsWidgetsForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FontControlsWidgetsForm)
{
    ui->setupUi(this);
    connect(ui->lineEdit, &QLineEdit::textEdited, this, &FontControlsWidgetsForm::lineEdit_textChanged);
    connect(ui->fontComboBox, &QFontComboBox::currentFontChanged, this, &FontControlsWidgetsForm::fontComboBox_currentFontChanged);
    connect(ui->pushButton, &QPushButton::clicked, this, &FontControlsWidgetsForm::pushButton_clicked);
}

FontControlsWidgetsForm::~FontControlsWidgetsForm()
{
    delete ui;
}

const QString FontControlsWidgetsForm::text()
{
    return ui->lineEdit->text();
}

void FontControlsWidgetsForm::lineEdit_textChanged(const QString &arg1)
{
    emit textChanged();
}

void FontControlsWidgetsForm::setText(const QString &text)
{
    ui->lineEdit->setText(text);
    emit textChanged();
}

const QString FontControlsWidgetsForm::font()
{
    return ui->fontComboBox->currentFont().family();
}

void FontControlsWidgetsForm::closeEvent(QCloseEvent *event) {
    QApplication::quit();
}

void FontControlsWidgetsForm::fontComboBox_currentFontChanged(const QFont &f)
{
    emit fontChanged();
}
