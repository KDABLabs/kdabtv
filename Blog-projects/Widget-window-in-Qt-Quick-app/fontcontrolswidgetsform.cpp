#include "fontcontrolswidgetsform.h"
#include "ui_fontcontrolswidgetsform.h"

FontControlsWidgetsForm::FontControlsWidgetsForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FontControlsWidgetsForm)
{
    ui->setupUi(this);
}

FontControlsWidgetsForm::~FontControlsWidgetsForm()
{
    delete ui;
}

QString FontControlsWidgetsForm::getText()
{
    return ui->lineEdit->text();
}

void FontControlsWidgetsForm::on_lineEdit_textChanged(const QString &arg1)
{
    emit textChanged();
}

void FontControlsWidgetsForm::setText(const QString &text)
{
    ui->lineEdit->setText(text);
    emit textChanged();
}

QString FontControlsWidgetsForm::getFont()
{
    return ui->fontComboBox->currentFont().family();
}

void FontControlsWidgetsForm::closeEvent(QCloseEvent *event) {
    QApplication::quit();
}

void FontControlsWidgetsForm::on_fontComboBox_currentFontChanged(const QFont &f)
{
    emit fontChanged();
}

