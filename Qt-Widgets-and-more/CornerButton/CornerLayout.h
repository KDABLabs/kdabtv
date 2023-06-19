#pragma once

#include <QObject>
#include <QPoint>

class CornerLayout : public QObject
{
    Q_OBJECT

public:
    explicit CornerLayout(QWidget *parent);
    void addWidget(QWidget *widget, Qt::Corner corner, const QPoint &offset = {});

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    void placeWidgets();

    QWidget *m_parentWidget = nullptr;

    struct LayoutItem
    {
        Qt::Corner corner;
        QWidget *widget;
        QPoint offset;
    };
    QVector<LayoutItem> m_layout;
};
