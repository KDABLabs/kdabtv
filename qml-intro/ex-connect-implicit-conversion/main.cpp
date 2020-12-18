/*************************************************************************
 *
 * Copyright (c) 2012-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget *window = new QWidget();
    window->setAttribute(Qt::WA_DeleteOnClose);
    QVBoxLayout* topLayout = new QVBoxLayout(window);

    // Set up the GUI
    QSlider* slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 100);

    QDoubleSpinBox* doubleSpin = new QDoubleSpinBox;
    doubleSpin->setDecimals( 1 );
    doubleSpin->setReadOnly( true );

    QHBoxLayout* horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(slider);
    horizontalLayout->addWidget(doubleSpin);
    topLayout->addLayout(horizontalLayout);

    // using pointer to member function
    QObject::connect(slider, &QSlider::valueChanged,
                     doubleSpin, &QDoubleSpinBox::setValue);
    // set the slider position and hence the QSpinBox value too
    slider->setValue(40);

    window->show();
    return app.exec();
}

