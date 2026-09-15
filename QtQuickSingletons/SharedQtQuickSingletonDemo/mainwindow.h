#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtQuickWidgets/QQuickWidget>
#include "nondefaultconstructiblesingleton.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    std::unique_ptr<Ui::MainWindow> ui;
    std::shared_ptr<NonDefaultConstructibleSingleton> m_singleton;
    void colorWhiteChangeRequest();
    void colorBlackChangeRequest();
    void setColor(QColor color);
    void replaceEngine1();
    void replaceEngine2();
};
#endif // MAINWINDOW_H
