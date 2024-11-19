#ifndef FONTCONTROLSWIDGETSFORM_H
#define FONTCONTROLSWIDGETSFORM_H

#include <QWidget>

namespace Ui {
class FontControlsWidgetsForm;
}

class FontControlsWidgetsForm : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ getText WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString font READ getFont NOTIFY fontChanged)

public:
    explicit FontControlsWidgetsForm(QWidget *parent = nullptr);
    ~FontControlsWidgetsForm();

    QString getText();
    void setText(const QString&);
    QString getFont();

signals:
    void textChanged();
    void fontChanged();
    void on_pushButton_clicked();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_lineEdit_textChanged(const QString &arg1);
    void on_fontComboBox_currentFontChanged(const QFont &f);

private:
    Ui::FontControlsWidgetsForm *ui;
};

#endif // FONTCONTROLSWIDGETSFORM_H
