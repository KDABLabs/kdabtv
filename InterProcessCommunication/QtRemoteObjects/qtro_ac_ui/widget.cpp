#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(SensorsReplica *replica, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , m_replica(replica)
{
    ui->setupUi(this);
    ui->statusLabel->setText(QMetaEnum::fromType<SensorsReplica::Status>().valueToKey(m_replica->status()));
    ui->targetTempLabel->setText(QString::number(m_replica->targetTemperature(), 'f', 2));
    ui->currentTempLabel->setText(QString::number(m_replica->currentTemperature(), 'f', 2));

    connect(replica, &SensorsReplica::statusChanged, this, [this] (SensorsReplica::Status status){
        ui->statusLabel->setText(QMetaEnum::fromType<SensorsReplica::Status>().valueToKey(status));
    });
    connect(replica, &SensorsReplica::targetTemperatureChanged, this, [this] (double targetTemp){
        ui->targetTempLabel->setText(QString::number(targetTemp, 'f', 2));
    });
    connect(replica, &SensorsReplica::currentTemperatureChanged, this, [this] (double currentTemp){
        ui->currentTempLabel->setText(QString::number(currentTemp, 'f', 2));
    });

    connect(ui->decToolButton, &QToolButton::clicked, this, [this]{
        m_replica->pushTargetTemperature(m_replica->targetTemperature() - 0.5);
    });
    connect(ui->incToolButton, &QToolButton::clicked, this, [this]{
        m_replica->pushTargetTemperature(m_replica->targetTemperature() + 0.5);
    });
}

Widget::~Widget()
{
    delete ui;
}

