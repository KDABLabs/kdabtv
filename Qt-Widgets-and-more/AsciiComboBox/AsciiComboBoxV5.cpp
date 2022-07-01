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

#include "AsciiComboBoxV5.h"
#include <QAbstractItemView>
#include <QCompleter>
#include <QDebug>
#include <QEvent>
#include <QLineEdit>
#include <QRegularExpression>

extern QStringList names;

namespace {
const int COMPLETION_ROLE = Qt::UserRole + 123;

class CustomRoleCompleter : public QCompleter
{
    Q_OBJECT
public:
    explicit CustomRoleCompleter(QObject *parent = nullptr)
        : QCompleter(parent)
    {
        setCompletionRole(COMPLETION_ROLE);
        setFilterMode(Qt::MatchContains);
        setCompletionMode(QCompleter::PopupCompletion);
        setCaseSensitivity(Qt::CaseInsensitive);
    }

    QString pathFromIndex(const QModelIndex &index) const override
    {
        return index.data(Qt::DisplayRole).toString();
    }
};

class ModelValidator : public QValidator
{
    Q_OBJECT
public:
    explicit ModelValidator(const QAbstractItemModel *model, QObject *parent = nullptr)
        : QValidator(parent)
        , m_model(model)
    {
    }
    State validate(QString &str, int &) const override
    {
        QStringMatcher matcher(str, Qt::CaseInsensitive);
        for (int row = 0, rows = m_model->rowCount(); row < rows; ++row) {
            const QString testString = m_model->index(row, 0).data(COMPLETION_ROLE).toString();
            if (matcher.indexIn(testString) != -1)
                return QValidator::Intermediate;
        }
        return QValidator::Invalid;
    }

private:
    const QAbstractItemModel *m_model;
};

} // end namespace

AsciiComboBoxV5::AsciiComboBoxV5(QWidget *parent)
    : QComboBox(parent)
{
    setEditable(true);

    auto customCompleter = new CustomRoleCompleter(this);
    customCompleter->setModel(model());
    setCompleter(customCompleter);
    setValidator(new ModelValidator(model(), this));

    setInsertPolicy(QComboBox::NoInsert);
    completer()->popup()->installEventFilter(this);
}

bool AsciiComboBoxV5::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::Hide) {
        auto index = completer()->popup()->currentIndex();
        if (index.isValid()) {
            // a match already set from the completer
            return QComboBox::eventFilter(watched, event);
        }

        index = completer()->currentIndex();
        if (index.isValid()) {
            // A partial match, lets use the match from the popup
            const QString text = index.data(Qt::DisplayRole).toString();
            lineEdit()->setText(text);
            emit textActivated(text);
        }
    }
    return QComboBox::eventFilter(watched, event);
}

void AsciiComboBoxV5::setValidValues(const QStringList &values)
{
    clear();

    for (const QString &value : values) {
        addItem(value);

        // Make it possible to complete Lukáš as Lukas
        // As completion is on substring, I'll keep both options in here
        setItemData(count() - 1, convertToAscii(value) + " / " + value, COMPLETION_ROLE);
    }
}

QString AsciiComboBoxV5::convertToAscii(QString str)
{
    str = str.replace("ł", "l");
    str = str.replace("æ", "ae");
    return str.normalized(QString::NormalizationForm_KD).remove(QRegularExpression("[^a-zA-Z\\s]"));
}

#include "AsciiComboBoxV5.moc"
