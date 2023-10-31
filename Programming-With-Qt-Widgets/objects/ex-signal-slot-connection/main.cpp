/*************************************************************************
 *
 * Copyright (c) 2010-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2010-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include <QtWidgets>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    auto window = new QWidget();
    window->setAttribute(Qt::WA_DeleteOnClose);
    auto layout = new QHBoxLayout(window);

    // Set up of the GUI
    auto slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 100);

    auto spin = new QSpinBox;
    spin->setReadOnly( true );

    layout->addWidget(slider);
    layout->addWidget(spin);

    // using pointer to member function
    QObject::connect(slider, &QSlider::valueChanged,
                     spin, &QSpinBox::setValue);

    // set the slider position and hence the QSpinBox value too
    slider->setValue(40);

    window->show();

    return app.exec();
}
