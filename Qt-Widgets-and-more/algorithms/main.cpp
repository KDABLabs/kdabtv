#include <QDebug>
#include <QVector>
#include <QWidget>
#include <kdalgorithms.h>
#include <ranges>
#include <vector>

const QVector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
const QVector<int> oddVector{1, 55, 27, 3};

void forEach()
{
    qDebug() << "========= for loop to print 1-10 =========";
    for (auto i : vec) {
        qDebug() << i;
    }

    qDebug() << "========= std::for_each to print 1-10 =========";
    std::for_each(vec.cbegin(), vec.cend(), [](int i) { qDebug() << i; });
}

void transformLoop()
{
    QVector<QString> result;
    for (auto i : vec) {
        result.append(QString::number(i));
    }
    qDebug() << "transform with loop:" << result;
}

namespace {
QString toString(int i)
{
    return QString::number(i);
}
}

void transformAlg()
{

    QVector<QString> result;
    std::transform(vec.cbegin(), vec.cend(), std::back_inserter(result), toString);
    qDebug() << "Transform with std::transform:" << result;
}

void transformRanges()
{
    QVector<QString> result;
    std::ranges::transform(vec, std::back_inserter(result), toString);
    qDebug() << "Transform with std::ranges:" << result;
}

#ifdef __cpp_lib_ranges_to_container
void transformInCpp23()
{
    auto result = vec | std::views::transform(...) | std::ranges::to<QVector>();
}
#endif

void transformKDAlg()
{
    const QVector<QString> result = kdalgorithms::transformed(vec, toString);
    qDebug() << "Transform with kdalgorithms:" << result;
}

void transformToStdVector()
{
    const auto toString = [](int i) { return QString::number(i); };
    const auto result = kdalgorithms::transformed<std::vector>(vec, toString);
    qDebug() << "Transform to std::vector:" << result;
}

void filteredWithLoop()
{
    QVector<int> result;
    for (auto i : vec) {
        if (i % 2 == 1)
            result.append(i);
    }
    qDebug() << "Odd numbers (filtered with loop):" << result;
}

void filtered()
{
    const auto isOdd = [](int num) { return num % 2 == 1; };
    const auto result = kdalgorithms::filtered(vec, isOdd);
    qDebug() << "Odd numbers:" << result;
}

void filtered2()
{
    const auto isGreatherThan = [](int num) { return [num](int value) { return value > num; }; };
    const auto result = kdalgorithms::filtered(vec, isGreatherThan(5));
    qDebug() << "Large numbers:" << result;
}

void filteredToTheMax()
{
    using namespace kdalgorithms::operators;

    const auto isOdd = [](int num) { return num % 2 == 1; };
    const auto isGreatherThan = [](int num) { return [num](int value) { return value > num; }; };
    const auto result = kdalgorithms::filtered(vec, isOdd && isGreatherThan(5));
    qDebug() << "Odd Large numbers:" << result;
}

void allOfWithLoop(const QString &title, const QVector<int> &vec)
{
    qDebug().noquote() << "loop -" << title;

    bool allOdd = true;
    for (auto i : vec) {
        if (i % 2 == 0) {
            allOdd = false;
            break;
        }
    }

    if (allOdd)
        qDebug("Yes");
    else
        qDebug("No");
}

void allOfWithAlgorithms(const QString &title, const QVector<int> &vec)
{
    qDebug().noquote() << "Algorithm -" << title;

    const auto isOdd = [](int num) { return num % 2 == 1; };
    if (kdalgorithms::all_of(vec, isOdd))
        qDebug("Yes");
    else
        qDebug("No");
}

int main()
{
    forEach();
    transformLoop();
    transformAlg();
    transformRanges();
    transformKDAlg();
    transformToStdVector();
    filteredWithLoop();
    filtered();
    filtered2();
    filteredToTheMax();

    allOfWithLoop("vec", vec);
    allOfWithLoop("oddVector", oddVector);
    allOfWithAlgorithms("vec", vec);
    allOfWithAlgorithms("oddVector", oddVector);
}
