#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nondefaultconstructiblesingleton.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->button1, &QPushButton::pressed, this, &MainWindow::colorWhiteChangeRequest);
    connect(ui->button2, &QPushButton::pressed, this, &MainWindow::colorBlackChangeRequest);
    connect(ui->replaceEngine1Button, &QPushButton::pressed, this, &MainWindow::replaceEngine1);
    connect(ui->replaceEngine2Button, &QPushButton::pressed, this, &MainWindow::replaceEngine2);
    qDebug() << ui->quickWidget1->engine()
             << ui->quickWidget2->engine()
             << (ui->quickWidget1->engine() == ui->quickWidget2->engine() ? "same engine" : "different engines");
    auto engine = ui->quickWidget1->engine();
    m_singleton = std::shared_ptr<NonDefaultConstructibleSingleton> { NonDefaultConstructibleSingleton::create(engine, engine) };
    connect(m_singleton.get(), &NonDefaultConstructibleSingleton::sharedColorChanged, this, &MainWindow::setColor);
    setColor(m_singleton->sharedColor().name());
}

MainWindow::~MainWindow()
{
}

void MainWindow::colorWhiteChangeRequest()
{
    const QColor color = "white";
    setColor(color);
    m_singleton.get()->setSharedColor(color);
}

void MainWindow::colorBlackChangeRequest()
{
    const QColor color = "black";
    setColor(color);
    m_singleton.get()->setSharedColor(color);
}

void MainWindow::setColor(QColor color)
{
    qDebug() << color;
    ui->label->setStyleSheet("QLabel { background-color : " + color.name() + "; }");
}

void MainWindow::replaceEngine1()
{
    ui->dockWidget1->widget()->close();
    delete ui->dockWidget1->widget();
    auto qqw = new QQuickWidget(ui->dockWidget1);
    qqw->setObjectName("quickWidget1");
    qqw->setResizeMode(QQuickWidget::SizeRootObjectToView);
    qqw->loadFromModule(u"com.kdab.sharedqtquicksingletondemo"_s, u"Quick"_s);
    ui->dockWidget1->setWidget(qqw);
}

void MainWindow::replaceEngine2()
{
    ui->dockWidget2->widget()->close();
    delete ui->dockWidget2->widget();
    auto qqw = new QQuickWidget(ui->dockWidget2);
    qqw->setObjectName("quickWidget2");
    qqw->setResizeMode(QQuickWidget::SizeRootObjectToView);
    qqw->loadFromModule(u"com.kdab.sharedqtquicksingletondemo"_s, u"Quick"_s);
    ui->dockWidget2->setWidget(qqw);
}
