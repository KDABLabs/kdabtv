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

    //Set up of GUI
    auto slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 100);

    auto spin = new QSpinBox;
    spin->setReadOnly( true );

    auto horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(slider);
    horizontalLayout->addWidget(spin);
    topLayout->addLayout(horizontalLayout);

    // using pointer to member function
    QObject::connect(slider, &QSlider::valueChanged,
                     spin, &QSpinBox::setValue);
    // set the slider position and hence the QSpinBox value too
    slider->setValue(40);

    // Uncommenting the following connect will result in a compile time error.
    // The signal passes no arguments whereas the slot is expecting a single
    // argument.
    // By using function pointers we get compile time parameter list checking.
    // Using the old-style SIGNAL/SLOT macros this would have been detected
    // as a run time warning only.
    //QObject::connect(slider, &QSlider::sliderPressed,
    //                 spin, &QSpinBox::setValue);

    auto textEdit = new QTextEdit();
    textEdit->setAttribute(Qt::WA_DeleteOnClose);

    // Uncommenting the following connect will result in a compile time error.
    // The signal is passing an incompatible parameter to the slot.
    // By using function pointers we get compile time parameter type conversion.
    // Using the old-style SIGNAL/SLOT macros this would have been detected
    // as a run time warning only.
    //QObject::connect(slider, &QSlider::sliderMoved,
    //                 textEdit, &QTextEdit::setFontFamily);

    window->show();
    return app.exec();
}

