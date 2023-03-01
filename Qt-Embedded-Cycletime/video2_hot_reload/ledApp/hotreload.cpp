#include "hotreload.h"
#include <QFileSystemWatcher>
#include <QDebug>
#include <QTimer>

Hotreload::Hotreload(QQmlApplicationEngine& engine, const QString &directory, QObject *parent):
    m_engine(engine)
{
    m_watcher = new QFileSystemWatcher(this);
    m_watcher->addPath(directory);

    connect(m_watcher, &QFileSystemWatcher::directoryChanged, this, [this, &engine](const QString& path){
        emit watchedSourceChanged();
    });
}

void Hotreload::clearCache()
{
    m_engine.clearComponentCache();
}
