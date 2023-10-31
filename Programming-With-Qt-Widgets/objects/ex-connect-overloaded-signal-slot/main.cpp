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
    auto window = new QWidget();
    window->setAttribute(Qt::WA_DeleteOnClose);
    auto topLayout = new QVBoxLayout(window);

    // Set up the GUI
    auto slider = new QSlider(Qt::Horizontal);
    slider->setRange(-100, 100);

    auto integerLcd = new QLCDNumber;
    integerLcd->setDigitCount( 3 );

    auto doubleSpin = new QDoubleSpinBox;
    doubleSpin->setRange( -1.0, 1.0 );
    doubleSpin->setSingleStep( 0.01 );

    auto doubleLcd = new QLCDNumber;
    doubleLcd->setDigitCount( 5 );

    auto integerHorizontalLayout = new QHBoxLayout;
    integerHorizontalLayout->addWidget(slider);
    integerHorizontalLayout->addWidget(integerLcd);
    topLayout->addLayout(integerHorizontalLayout);

    auto doubleHorizontalLayout = new QHBoxLayout;
    doubleHorizontalLayout->addWidget(doubleSpin);
    doubleHorizontalLayout->addWidget(doubleLcd);
    topLayout->addLayout(doubleHorizontalLayout);

    // Uncommenting the following connect statement would result in a
    // "unresolved function pointer" compile error.
    // QObject::connect(slider, &QSlider::valueChanged,
    //                  integerLcd, &QLCDNumber::display);
    // This is due the fact that QLCDNumber::display() is overloaded and we
    // have to clarify which overload we intend to use.
    // This is done by casting the function pointer to the appropriate type.
    QObject::connect(slider,
                     &QSlider::valueChanged,
                     integerLcd,
                     static_cast<void(QLCDNumber::*)(int)>
                        (&QLCDNumber::display));


    // In Qt 5.7 there's an easier syntax for selecting the right overload:
    //
    // QOverload::of<arguments>(&Class::function)
    //
    // If the function is overloaded over const, one can use QConstOverload and
    // QNonConstOverload to pick the right one.
    //
    // The above connect statement could be therefore rewritten as this:

//    QObject::connect(slider,
//                     &QSlider::valueChanged,
//                     integerLcd,
//                     QOverload<int>::of(&QLCDNumber::display));


    // Also in Qt 5.7, if C++14 is enabled (CONFIG += c++14 in the .pro file),
    // there's a even easier syntax using qOverload:
    //
    // qOverload<arguments>(&Class::function)
    //
    // If the function is overloaded over const, one can use qConstOverload and
    // qNonConstOverload to pick the right one.
    //
    // For example:

//    QObject::connect(slider,
//                     &QSlider::valueChanged,
//                     integerLcd,
//                     qOverload<int>(&QLCDNumber::display));


    // set the slider position and hence the QLCDNumber value too
    slider->setValue(40);

    // In the following connect statement the signal
    // QDoubleSpinBox::valueChanged is also overloaded
    QObject::connect(doubleSpin,
                     static_cast<void(QDoubleSpinBox::*)(double)>
                        (&QDoubleSpinBox::valueChanged),
                     doubleLcd,
                     static_cast<void(QLCDNumber::*)(double)>
                        (&QLCDNumber::display));
    // set the QDoubleSpinBox value and hence the QLCDNumber value too
    doubleSpin->setValue(-0.5);

    window->show();
    return app.exec();
}

