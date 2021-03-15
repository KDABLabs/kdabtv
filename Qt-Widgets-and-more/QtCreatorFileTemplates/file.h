#pragma once
 
#include <Dashlets/DashletWidget.h>
#include <memory>
 
namespace Ui {
class %{CN};
}
 
class %{CN} : public Dashlets::DashletWidget
{
    Q_OBJECT
public:
    explicit %{CN}(QWidget *parent = nullptr);
    ~%{CN}();
    static QStringList path() { return {"%{JS: "%{DashletPath}".split("/").join("\\\" ,\\\"")}"}; }
 
private:
    std::unique_ptr<Ui::%{CN}> ui;
};
