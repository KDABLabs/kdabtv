#ifndef CPUGPUCHART_H
#define CPUGPUCHART_H

#include <QQuickPaintedItem>
#include <QProcess>



template <typename T>
class asKeyValueRange
{
public:
    asKeyValueRange(T &data)
        : m_data{data}
    {
    }

    auto begin() { return m_data.keyValueBegin(); }

    auto end() { return m_data.keyValueEnd(); }

private:
    T &m_data;
};



class CpuGpuchart : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit CpuGpuchart(QQuickItem *parent = nullptr);

    virtual void paint(QPainter* painter) override;

private:
    QMap<QString, QString> m_gpuinfo;
    QTimer* m_updateTimer;
    QProcess m_gpuProcess;
};

#endif // CPUGPUCHART_H
