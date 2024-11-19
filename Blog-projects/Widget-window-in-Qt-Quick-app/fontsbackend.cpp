#include "fontsbackend.h"

#include <QFontDatabase>

FontsBackend::FontsBackend(QObject *parent)
    : QObject{parent}
{
}

QStringList FontsBackend::fontList()
{
    return QFontDatabase::families();
}
