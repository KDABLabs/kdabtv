#pragma once

#include <QPushButton>

class DoubleClickButton2 : public QPushButton
{
    Q_OBJECT

public:
    DoubleClickButton2(const QString &text, QWidget *parent = nullptr);

signals:
    void doubleClicked();

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    class QTimer *m_timer;
};
