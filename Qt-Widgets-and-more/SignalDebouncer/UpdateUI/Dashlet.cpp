#include "Dashlet.h"
#include "KDSignalThrottler.h"
#include "ui_Dashlet.h"
#include <QApplication>
#include <QThread>

Dashlet::Dashlet(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Dashlet)
{
    ui->setupUi(this);
#if 1
    connect(ui->year, &QSpinBox::valueChanged, this, &Dashlet::updateUI);
    connect(ui->employeeGroup, &QComboBox::currentTextChanged, this, &Dashlet::updateUI);
    connect(ui->data, &QComboBox::currentTextChanged, this, &Dashlet::updateUI);
    updateUI();
#else
    auto bouncer = new KDToolBox::KDSignalDebouncer(this);
    bouncer->setTimeout(1000);
    connect(ui->year, &QSpinBox::valueChanged, bouncer, &KDToolBox::KDSignalDebouncer::throttle);
    connect(ui->employeeGroup, &QComboBox::currentTextChanged, bouncer,
            &KDToolBox::KDSignalDebouncer::throttle);
    connect(ui->data, &QComboBox::currentTextChanged, bouncer,
            &KDToolBox::KDSignalDebouncer::throttle);

    connect(bouncer, &KDToolBox::KDSignalDebouncer::triggered, this, &Dashlet::setupPlot);
    bouncer->throttle();
#endif
}

void Dashlet::setConfig(const DashletConfig &config)
{
    ui->year->setValue(config.year);
    ui->employeeGroup->setCurrentText(config.group);
    ui->data->setCurrentText(config.data);
}

Dashlet::~Dashlet() = default;

void Dashlet::updateUI()
{
    qDebug() << "Setting up!";
    ui->plot->setText("Setting up....");

    // make it slow on purpose, to emulate a slow updateUI.
    qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    QThread::sleep(2);

    ui->plot->setText(QString("Year: %1<br>Employee Group: %2<br>Data: %3")
                          .arg(ui->year->text())
                          .arg(ui->employeeGroup->currentText())
                          .arg(ui->data->currentText()));
}
