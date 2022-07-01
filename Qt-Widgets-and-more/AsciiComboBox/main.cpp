/* MIT License

Copyright (C) 2022 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "AsciiComboBoxV1.h"
#include "AsciiComboBoxV2.h"
#include "AsciiComboBoxV3.h"
#include "AsciiComboBoxV4.h"
#include "AsciiComboBoxV5.h"
#include <QApplication>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>

QStringList names{"Lukáš Tinkl",
                  "Lukas Graham",
                  "Miłosz Kosobucki",
                  "Jesper Kjær Pedersen",
                  "Alma",
                  "Ida",
                  "Freja",
                  "Clara",
                  "Ella",
                  "Emma",
                  "Olivia",
                  "Agnes",
                  "Sofia",
                  "Nora",
                  "Anna",
                  "Karla",
                  "Luna",
                  "Asta",
                  "Ellie",
                  "Laura",
                  "Lily",
                  "Alberte",
                  "Esther",
                  "Frida",
                  "Josefine",
                  "Ellen",
                  "Aya",
                  "Astrid",
                  "Merle",
                  "Isabella",
                  "Lærke",
                  "Saga",
                  "Mathilde",
                  "Liva",
                  "Mille",
                  "Hannah",
                  "Victoria",
                  "Maja",
                  "Marie",
                  "Vilma",
                  "Sofie",
                  "Emily",
                  "Andrea",
                  "Molly",
                  "Gry",
                  "Lea",
                  "Liv",
                  "Vera",
                  "Leonora",
                  "Rosa",
                  "Johanne",
                  "Alva",
                  "Emilie",
                  "Alba",
                  "Oscar",
                  "Karl",
                  "William",
                  "Alfred",
                  "Oliver",
                  "Arthur",
                  "Lucas",
                  "Valdemar",
                  "August",
                  "Noah",
                  "Malthe",
                  "Aksel",
                  "Emil",
                  "Victor",
                  "Theo",
                  "Elias",
                  "Viggo",
                  "Otto",
                  "Magnus",
                  "Liam",
                  "Elliot",
                  "Nohr",
                  "Felix",
                  "Anton",
                  "Matheo",
                  "Alexander",
                  "Frederik",
                  "Louie",
                  "Hugo",
                  "Theodor",
                  "Albert",
                  "Lauge",
                  "Anker",
                  "Konrad",
                  "Storm",
                  "Villads",
                  "Villum",
                  "Milas",
                  "Johan",
                  "Vincent",
                  "Adam",
                  "Christian",
                  "Erik",
                  "Marius",
                  "Walter",
                  "Pelle",
                  "Kalle",
                  "Birk",
                  "Philip"};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto window = new QWidget;
    auto layout = new QVBoxLayout(window);

    auto addToLayout = [&](const QString &title, auto comboBox) {
        layout->addWidget(new QLabel(title));
        comboBox->setValidValues(names);
        QObject::connect(comboBox, &QComboBox::textActivated, [&](const QString &str) {
            qDebug() << title << "item activated: " << str;
        });

        layout->addWidget(comboBox);
    };

    addToLayout("Version 1", new AsciiComboBoxV1);
    addToLayout("Version 2", new AsciiComboBoxV2);
    addToLayout("Version 3", new AsciiComboBoxV3);
    addToLayout("Version 4", new AsciiComboBoxV4);
    addToLayout("Version 5", new AsciiComboBoxV5);

    window->show();
    return a.exec();
}
