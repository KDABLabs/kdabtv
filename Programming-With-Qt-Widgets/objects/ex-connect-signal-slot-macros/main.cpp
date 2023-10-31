/*************************************************************************
 *
 * Copyright (c) 2008-2011, Nokia Corporation and/or its subsidiary(-ies).
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
    auto window = new QWidget();
    window->setAttribute(Qt::WA_DeleteOnClose);
    auto topLayout = new QVBoxLayout(window);

    // Set up of GUI
    auto slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 100);

    auto spin = new QSpinBox;
    spin->setReadOnly( true );

    auto horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(slider);
    horizontalLayout->addWidget(spin);
    topLayout->addLayout(horizontalLayout);

    QObject::connect(slider, &QAbstractSlider::valueChanged,
                     spin, &QSpinBox::setValue);
    slider->setValue(40);

    window->show();
    return app.exec();
}
