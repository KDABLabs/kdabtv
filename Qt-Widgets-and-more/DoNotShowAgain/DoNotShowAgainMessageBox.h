#pragma once

#include <QMessageBox>

class DoNotShowAgainMesageBox : public QMessageBox
{
    Q_OBJECT
public:
    static StandardButton information(const QString &key, QWidget *parent, const QString &title,
                                      const QString &text,
                                      QMessageBox::StandardButtons buttons = Ok,
                                      QMessageBox::StandardButton defaultButton = NoButton);
    static void clearAll();

    StandardButton execute();

private:
    explicit DoNotShowAgainMesageBox(const QString &key, QWidget *parent = nullptr);

    QString m_key;
};
