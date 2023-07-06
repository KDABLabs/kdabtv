/* MIT License

Copyright (C) 2023 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

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

#include "Form.h"
#include <QDebug>
#include <QEvent>

namespace {
// Taken from https://github.com/KDAB/KDAlgorithms
template <typename Value, typename ContainerValue>
bool value_in(Value &&value, std::initializer_list<ContainerValue> container)
{
    return std::find(std::cbegin(container), std::cend(container), std::forward<Value>(value))
        != std::cend(container);
}

class ReadOnlyHelper : public QObject
{
    Q_OBJECT
public:
    static ReadOnlyHelper &instance()
    {
        static ReadOnlyHelper instance;
        return instance;
    }

    void makeReadOnly(QWidget *widget)
    {
        const auto children = widget->findChildren<QWidget *>();
        for (auto child : children)
            child->installEventFilter(this);
    }

protected:
    bool eventFilter(QObject *object, QEvent *event) override
    {
        if (value_in(event->type(),
                     {
                         QEvent::MouseButtonPress,
                         QEvent::MouseButtonRelease,
                         QEvent::MouseButtonDblClick,
                         QEvent::MouseMove,

                         QEvent::Wheel,

                         QEvent::KeyPress,
                         QEvent::KeyRelease,
                     }))
            return true;
        else
            return QObject::eventFilter(object, event);
    }
};
} // end namespace

void part4()
{
    qDebug() << "========== ReadOnly - part4 ==========";
    auto form = new Form;
    ReadOnlyHelper::instance().makeReadOnly(form);
    form->show();
}

#include "part4.moc"
