#pragma once

#include <QObject>
#include <QColor>

class CppSingleton : public QObject
{
    Q_OBJECT

private:
    // Hide regular constructor
    CppSingleton() = default;

public:
    // Disable copy constructor
    CppSingleton(const CppSingleton& obj) = delete;
    CppSingleton& operator=(CppSingleton const&) = delete;
    static std::shared_ptr<CppSingleton> instance();

    QColor sharedColor();
    void setSharedColor(QColor color);

signals:
    void sharedColorChanged(QColor color);

private:
    QColor m_sharedColor = "white";
};
