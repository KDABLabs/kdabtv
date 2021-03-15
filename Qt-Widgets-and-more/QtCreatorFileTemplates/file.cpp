#include "%{CN}.h"
#include "ui_%{CN}.h"
#include <Widgets/SystemBurgerButton.h>
 
%{CN}::%{CN}(QWidget *parent)
    : Dashlets::DashletWidget(path(), parent)
    , ui(new Ui::%{CN})
{
    ui->setupUi(this);
}
 
%{CN}::~%{CN}() = default;
