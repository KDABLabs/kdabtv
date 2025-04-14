#include "Storage.h"

Storage::Storage()
{
    using namespace Medium;
    // source: https://en.wikipedia.org/wiki/Depeche_Mode_discography
    m_albums = {
        // clang-format off
        {"Speak & Spell",            1981, "Mute",           CD | CS | LP,            10, 28, -1,  -1, 49, 99, -1, 21, -1, 192},
        {"A Broken Frame",           1982, "Mute",           CD | CS | LP,            8,  -1, -1, 194, 56, 88, -1, 22, -1, 177},
        {"Construction Time Again ", 1983, "Mute",           CD | CS | LP,            6,  -1, -1,  -1,  7, -1, 32, 12, 21,  -1},
        {"Some Great Reward",        1984, "Mute",           CD | CS | LP,            5,  -1, 19,  -1,  3, 32, 34,  7,  5,  51},
        {"Black Celebration",        1986, "Mute",           CD | CS | LP,            4,  69, 26,  19,  2, 17, 35,  5,  1,  90},
        {"Music for the Masses",     1987, "Mute",           CD | CS | LP,            10, 60, 16,   7,  2,  7, 52,  4,  4,  35},
        {"Violator",                 1990, "Mute",           CD | CS | LP | DCC | MD, 2,  42,  4,   1,  2,  5, 17,  6,  2,   7},
        {"Songs of Faith and Devotion", 1993, "Mute",        CD | CS | LP | DCC | MD, 1,  14,  1,   1,  1,  1, 18,  2,  1,   1},
        {"Ultra",                    1997, "Mute",           CD | CS | LP | DCC,      1,   7,  5,   2,  1,  2, 17,  1,  4,   5},
        {"Exciter",                  2001, "Mute",           CD | CS | LP,            9,  20,  2,   1,  1,  2, 15,  1,  2,   8},
        {"Playing the Angel",        2005, "Mute,Reprise",   CD | LP | DOWNLOAD,      6,  45,  1,   1,  1,  1, 11,  1,  1,   7},
        {"Sounds of the Universe",   2009, "Mute",           CD | LP | DOWNLOAD,      2,  32,  1,   2,  1,  1,  7,  1,  1,   3},
        {"Delta Machine",            2013, "Mute, Columbia", CD | LP | DOWNLOAD,      2,  16,  1,   2,  1,  1,  3,  1,  1,   6},
        {"Spirit",                   2017, "Mute, Columbia", CD | LP | DOWNLOAD,      5,  14,  1,   1,  1,  1,  4,  3,  1,   5},
        {"Memento Mori",             2023, "Mute, Columbia", CD | LP | CS | DOWNLOAD, 2,  36,  1,   1,  1,  1,  3,  1,  1,  14},
        // clang-format on
    };
}

int Storage::albumCount() const
{
    return m_albums.size();
}

AlbumInformation Storage::album(int index) const
{
    return m_albums.at(index);
}
