#ifndef HOTRELOAD_H
#define HOTRELOAD_H

#include <QObject>
#include <QQmlApplicationEngine>

class QFileSystemWatcher;


class Hotreload : public QObject
{
    Q_OBJECT
public:
    explicit Hotreload(QQmlApplicationEngine& engine, const QString& directory, QObject *parent = nullptr);

signals:
    void watchedSourceChanged();

public slots:
    void clearCache();

private:
    QFileSystemWatcher *m_watcher;
    QQmlApplicationEngine& m_engine;

};

#endif // HOTRELOAD_H
