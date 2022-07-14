/* MIT License

Copyright (C) 2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

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

#pragma once

#include <QAbstractListModel>
#include <QPixmap>
#include <QVector>

class DepecheModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit DepecheModel(QObject *parent = nullptr);

    enum class Column {
        Year,
        RecordLabel,
        CD,
        CS,
        LP,
        DCC,
        MD,
        download,
        UK,
        AUS,
        AUT,
        FRA,
        GER,
        ITA,
        NLD,
        SWE,
        SWI,
        US,
        COLUMNCOUNT
    };
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    struct Data
    {
        QString album;
        int year;
        QString recordLabel;
        bool CD;
        bool CS;
        bool LP;
        bool DCC;
        bool MD;
        bool download;
        int UK;
        int AUS;
        int AUT;
        int FRA;
        int GER;
        int ITA;
        int NLD;
        int SWE;
        int SWI;
        int US;
    };
    QVector<Data> m_data;
    QPixmap m_pix;
};
