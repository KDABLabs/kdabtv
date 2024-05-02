#pragma once

#include <QWidget>
#include <memory>

namespace Ui {
class Dashlet;
}

struct DashletConfig
{
    int year;
    QString group;
    QString data;
};

class Dashlet : public QWidget
{
    Q_OBJECT

public:
    explicit Dashlet(QWidget *parent = nullptr);
    void setConfig(const DashletConfig &config);
    ~Dashlet();

private:
    void updateUI();

    std::unique_ptr<Ui::Dashlet> ui;
};
