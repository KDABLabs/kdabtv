/*************************************************************************
 *
 * Copyright (c) 2012-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include <QtWidgets>

// this is a functor
struct LogString {
  explicit LogString(const QString & prefix) : m_prefix(prefix) {}

  void operator () (const QString &string) {
    qDebug() << m_prefix + string;
  }

private:
  QString m_prefix;
};

void myStandAloneFunction() {
    QApplication::quit();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    auto window = new QWidget();
    window->setAttribute(Qt::WA_DeleteOnClose);
    auto topLayout = new QVBoxLayout(window);

    // Set up of the GUI
    auto slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 100);

    auto spin = new QSpinBox;
    spin->setReadOnly( true );

    auto horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(slider);
    horizontalLayout->addWidget(spin);
    topLayout->addLayout(horizontalLayout);

    auto lineEdit = new QLineEdit;
    topLayout->addWidget(lineEdit);

    auto quitButton = new QPushButton("Click to quit");
    topLayout->addWidget(quitButton);

    auto pressMeButton = new QPushButton("Press Me!");
    topLayout->addWidget(pressMeButton);

    // using pointer to member function
    QObject::connect(slider, &QSlider::valueChanged,
                     spin, &QSpinBox::setValue);
    // set the slider position and hence the QSpinBox value too
    slider->setValue(40);

    // using a functor
    QObject::connect(lineEdit, &QLineEdit::textChanged, LogString("Log: "));

    // using a lambda function
    QObject::connect(pressMeButton, &QPushButton::pressed,
                     [pressMeButton] {pressMeButton->setText("Release Me!");});
    QObject::connect(pressMeButton, &QPushButton::released,
                     [pressMeButton] {pressMeButton->setText("Press Me!");});

    // using a stand alone function pointer
    QObject::connect(quitButton, &QPushButton::clicked,
                     myStandAloneFunction);

    // Using a context object to break the connection (when the context object
    // is destroyed)
    auto selfDestroyingLabel = new QLabel("Click the button in the other window."
                                             "Then close this window and reclick the button.");
    selfDestroyingLabel->setWordWrap(true);
    selfDestroyingLabel->resize(400, 200);

    // make the label delete itself when it gets closed
    selfDestroyingLabel->setAttribute(Qt::WA_DeleteOnClose);

    QObject::connect(pressMeButton, &QPushButton::clicked, selfDestroyingLabel,
                     [selfDestroyingLabel] {
        selfDestroyingLabel->setText(selfDestroyingLabel->text() +
                                     "\nButton clicked!");
    });

    window->show();
    selfDestroyingLabel->show();

    window->raise();
    window->activateWindow();

    return app.exec();
}

