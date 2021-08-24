#pragma once

#include <QObject>

class Converters : public QObject
{
    Q_OBJECT

public:
    void test(int foo, bool bar);

protected slots:
    void go();
    void complexStuff();
};
