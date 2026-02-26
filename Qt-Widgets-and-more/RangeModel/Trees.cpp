// Copyright (C) 2025 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

// Simplified version of code from
// https://github.com/qt/qtbase/blob/dev/tests/manual/corelib/itemmodels/qrangemodel/main.cpp

#include <QRangeModel>
#include <QTreeView>
#include <vector>

namespace {
struct TreeRow;
using Tree = std::vector<TreeRow>;

struct TreeRow
{
public:
    TreeRow(const QString &region, const QString &capital)
        : m_region(region)
        , m_capital(capital)
    {
    }

    template <typename... Args>
    TreeRow &addChild(Args &&...args)
    {
        if (!m_children)
            m_children.emplace(Tree{});
        TreeRow &res = m_children->emplace_back(args...);
        res.m_parent = this;
        return res;
    }

    // tree traversal protocol implementation
    TreeRow *parentRow() const { return m_parent; }
    const std::optional<Tree> &childRows() const { return m_children; }

private:
    QString m_region;
    QString m_capital;

    TreeRow *m_parent = nullptr;
    std::optional<Tree> m_children = std::nullopt;

#if 1 // Yes this is needed for non gadgets...
    template <size_t I, typename Row,
              std::enable_if_t<std::is_same_v<q20::remove_cvref_t<Row>, TreeRow>, bool> = true>
    friend inline auto &&get(Row &&row)
    {
        if constexpr (I == 0)
            return q23::forward_like<Row>(row.m_region);
        else if constexpr (I == 1)
            return q23::forward_like<Row>(row.m_capital);
    }
#endif
};
} // namespace

#if 1
namespace std {
template <>
struct tuple_size<TreeRow> : std::integral_constant<size_t, 2>
{
};
template <size_t I>
struct tuple_element<I, TreeRow>
{
    using type = q20::remove_cvref_t<decltype(get<I>(std::declval<TreeRow>()))>;
};
} // namespace std
#endif

namespace {
QRangeModel *makeTree()
{
    static Tree europe = {{"Germany", "Berlin"}, {"France", "Paris"}, {"Austria", "Vienna"}};

    TreeRow &bavaria = europe[0].addChild("Bavaria", "Munich");
    bavaria.addChild("Upper Bavaria", "München");
    bavaria.addChild("Lower Bavaria", "Landshut");
    bavaria.addChild("Upper Palatinate", "Regensburg");
    bavaria.addChild("Swabia", "Augsburg");
    bavaria.addChild("Franconia", "Nürnberg");
    bavaria.addChild("Upper Franconia", "Bayreuth");
    bavaria.addChild("Middle Franconia", "Ansbach");
    bavaria.addChild("Lower Franconia", "Würzburg");

    TreeRow &hessia = europe[0].addChild("Hessia", "Wiesbaden");
    hessia.addChild("Upper Hesse", "Giessen");
    hessia.addChild("Lower Hesse", "Darmstadt");
    hessia.addChild("North Hesse", "Kassel");

    europe[1].addChild("Île-de-France", "Paris");
    europe[1].addChild("Provence-Alpes-Côte d'Azur", "Marseille");
    europe[1].addChild("Auvergne-Rhône-Alpes", "Lyon");
    europe[1].addChild("Nouvelle-Aquitaine", "Bordeaux");

    europe[2].addChild("Vienna", "Vienna");
    europe[2].addChild("Lower Austria", "St. Pölten");
    europe[2].addChild("Upper Austria", "Linz");
    europe[2].addChild("Styria", "Graz");
    europe[2].addChild("Carinthia", "Klagenfurt");
    europe[2].addChild("Salzburg", "Salzburg");
    europe[2].addChild("Tyrol", "Innsbruck");
    europe[2].addChild("Vorarlberg", "Bregenz");
    europe[2].addChild("Burgenland", "Eisenstadt");

    return new QRangeModel(std::ref(europe));
}
} // namespace

void trees()
{
    {
        auto view = new QTreeView;
        auto model = makeTree();
        view->setModel(model);
        view->show();
    }
}
