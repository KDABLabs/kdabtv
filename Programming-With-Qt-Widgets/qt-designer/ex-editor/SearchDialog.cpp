#include "SearchDialog.h"
#include "ui_SearchDialog.h"
#include <QDebug>

SearchDialog::SearchDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::SearchDialog) {
  ui->setupUi(this);
  //  ui->asRegularExpression->setChecked(true);
  connect(ui->asRegularExpression, &QCheckBox::toggled, this,
          &SearchDialog::updateUIState);
  connect(ui->caseSensitive, &QCheckBox::toggled, this,
          &SearchDialog::updateUIState);
  updateUIState();
  on_wholeWord2_clicked(true);
}

SearchDialog::~SearchDialog() { delete ui; }

void SearchDialog::updateUIState() {
  ui->wholeWord2->setEnabled(ui->asRegularExpression->isChecked() &&
                             ui->caseSensitive->isChecked());
}

void SearchDialog::on_wholeWord2_clicked(bool checked) {
  qDebug() << "Hello" << checked;
}
