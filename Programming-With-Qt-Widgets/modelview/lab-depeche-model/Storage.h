#pragma once
#include <QFlags>
#include <QString>
#include <QVector>

namespace Medium {
enum Medium {
    CD = 0x1,
    CS = 0x2,
    LP = 0x4,
    DCC = 0x8,
    MD = 0x10,
    DOWNLOAD = 0x20,
};
Q_DECLARE_FLAGS(Mediums, Medium);
Q_DECLARE_OPERATORS_FOR_FLAGS(Mediums)
} // namespace Medium

struct AlbumInformation
{
    QString album;
    int year;
    QString recordLabel;
    Medium::Mediums mediums;
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

class Storage
{
public:
    Storage();
    int albumCount() const;
    AlbumInformation album(int index) const;

private:
    QVector<AlbumInformation> m_albums;
};
