#include "fontcontrolswidgetsform.h"
#include "ui_fontcontrolswidgetsform.h"

FontControlsWidgetsForm::FontControlsWidgetsForm(QWidget *parent)
    : QWidget(parent)
    , ui(std::make_unique<Ui::FontControlsWidgetsForm>())
{
    ui->setupUi(this);
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &FontControlsWidgetsForm::textChanged);
    connect(ui->fontComboBox, &QFontComboBox::currentFontChanged, this, &FontControlsWidgetsForm::fontFamilyChanged);
    connect(ui->pushButton, &QPushButton::clicked, this, &FontControlsWidgetsForm::buttonClicked);
}

FontControlsWidgetsForm::~FontControlsWidgetsForm() = default;

QString FontControlsWidgetsForm::text() const
{
    return ui->lineEdit->text();
}

void FontControlsWidgetsForm::setText(const QString &text)
{
    ui->lineEdit->setText(text);
}

QString FontControlsWidgetsForm::fontFamily() const
{
    return ui->fontComboBox->currentFont().family();
}

void FontControlsWidgetsForm::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    QApplication::quit();
}
