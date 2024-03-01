/*************************************************************************
 *
 * Copyright (c) 2008-2010, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2010-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#ifndef COUNTRYSELECTOR_H
#define COUNTRYSELECTOR_H

#include <QWidget>
class QCompleter;
class QCheckBox;
class QComboBox;

class CountrySelector :public QWidget
{
    Q_OBJECT

public:
    explicit CountrySelector(QWidget *parent = nullptr);

protected slots:
    void changeComlpetionMode(int index);
    void changeCaseSensitivity(int index);

protected:
    QStringList countries();

private:
    QComboBox* m_mode;
    QComboBox* m_caseSensitivity;
    QCheckBox* m_wrap;
    QCompleter* m_completer;
};



#endif /* COUNTRYSELECTOR_H */

