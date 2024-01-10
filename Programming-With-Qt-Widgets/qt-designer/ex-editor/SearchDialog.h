#pragma once

#include <QDialog>

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog {
  Q_OBJECT

public:
  explicit SearchDialog(QWidget *parent = nullptr);
  ~SearchDialog();

private slots:
  void on_wholeWord2_clicked(bool checked);

private:
  void updateUIState();
  Ui::SearchDialog *ui;
};
