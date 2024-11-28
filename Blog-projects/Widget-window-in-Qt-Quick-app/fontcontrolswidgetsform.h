#ifndef FONTCONTROLSWIDGETSFORM_H
#define FONTCONTROLSWIDGETSFORM_H

#include <QWidget>

namespace Ui {
class FontControlsWidgetsForm;
}

class FontControlsWidgetsForm : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString font READ font NOTIFY fontChanged)

public:
    explicit FontControlsWidgetsForm(QWidget *parent = nullptr);
    ~FontControlsWidgetsForm();

    const QString text();
    void setText(const QString&);
    const QString font();

signals:
    void textChanged();
    void fontChanged();
    void pushButton_clicked();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void lineEdit_textChanged(const QString &arg1);
    void fontComboBox_currentFontChanged(const QFont &f);

private:
    Ui::FontControlsWidgetsForm *ui;
};

#endif // FONTCONTROLSWIDGETSFORM_H
