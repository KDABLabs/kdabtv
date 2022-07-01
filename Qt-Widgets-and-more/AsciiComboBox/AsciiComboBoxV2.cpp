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

#include "AsciiComboBoxV2.h"
#include <QCompleter>
#include <QRegularExpression>
static const int COMPLETION_ROLE = Qt::UserRole + 123;

AsciiComboBoxV2::AsciiComboBoxV2(QWidget *parent)
    : QComboBox(parent)
{
    setEditable(true);
    setInsertPolicy(QComboBox::NoInsert);

    completer()->setCompletionRole(COMPLETION_ROLE);
    completer()->setFilterMode(Qt::MatchContains);
    completer()->setCompletionMode(QCompleter::PopupCompletion);
    completer()->setCaseSensitivity(Qt::CaseInsensitive);
}

void AsciiComboBoxV2::setValidValues(const QStringList &values)
{
    clear();

    for (const QString &value : values) {
        addItem(value);

        // Make it possible to complete Lukáš as Lukas
        // As completion is on substring, I'll keep both options in here
        setItemData(count() - 1, convertToAscii(value) + " / " + value, COMPLETION_ROLE);
    }
}

QString AsciiComboBoxV2::convertToAscii(QString str)
{
    str = str.replace("ł", "l");
    str = str.replace("æ", "ae");
    return str.normalized(QString::NormalizationForm_KD).remove(QRegularExpression("[^a-zA-Z\\s]"));
}
