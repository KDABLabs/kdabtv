#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "rep_Sensors_replica.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(SensorsReplica *replica, QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    std::unique_ptr<SensorsReplica> m_replica;
};
#endif // WIDGET_H
