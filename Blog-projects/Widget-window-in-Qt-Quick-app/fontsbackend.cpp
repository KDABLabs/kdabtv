#include "fontsbackend.h"

#include <QFontDatabase>

FontsBackend::FontsBackend(QObject *parent)
    : QObject{parent}
{
}

const QStringList FontsBackend::fontList()
{
    return QFontDatabase::families();
}
