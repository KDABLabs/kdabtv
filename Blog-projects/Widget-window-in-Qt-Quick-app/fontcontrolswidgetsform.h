#pragma once

#include <QWidget>

namespace Ui {
class FontControlsWidgetsForm;
}

class FontControlsWidgetsForm : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString fontFamily READ fontFamily NOTIFY fontFamilyChanged)

public:
    explicit FontControlsWidgetsForm(QWidget *parent = nullptr);
    ~FontControlsWidgetsForm();

    QString text() const;
    void setText(const QString&);
    QString fontFamily() const;

signals:
    void textChanged();
    void fontFamilyChanged();
    void buttonClicked();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    std::unique_ptr<Ui::FontControlsWidgetsForm> ui;
};
