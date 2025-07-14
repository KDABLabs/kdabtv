/*************************************************************************
 *
 * Copyright (c) 2008-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2012-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include <QtWidgets>

void setupTable()
{
    auto model = new QStandardItemModel(10, 10);
    for (int row = 0; row < 10; ++row) {
        for (int col = 0; col < 10; ++col) {
            model->setData(model->index(row, col), QString("(%1,%2)").arg(row).arg(col));
        }
    }
    auto table = new QTableView;
    table->setAttribute(Qt::WA_DeleteOnClose);
    table->setModel(model);
    table->show();
    table->resize(800, 600);
}

namespace {
constexpr int URLRole = Qt::UserRole + 1;
}

void setupTree()
{
    auto model = new QStandardItemModel;
    model->setHorizontalHeaderLabels({"Title", "Description"});
    QStandardItem *root = model->invisibleRootItem();

    auto add = [&](QStandardItem *parent, const QString &title, const QString &description,
                   const QString &url) {
        auto titleItem = new QStandardItem(title);
        titleItem->setData(url, URLRole);
        titleItem->setFlags(titleItem->flags() & ~Qt::ItemIsEditable);

        auto descriptionItem = new QStandardItem(description);
        descriptionItem->setData(url, URLRole);
        descriptionItem->setFlags(titleItem->flags() & ~Qt::ItemIsEditable);

        parent->appendRow({titleItem, descriptionItem});
    };

    auto youtube = new QStandardItem("YouTube");
    youtube->setData("https://www.youtube.com/channel/UCjsJkTJSZ5G7ewH2uf08t0A", URLRole);
    youtube->setFlags(youtube->flags() & ~Qt::ItemIsEditable);
    root->appendRow(youtube);

    add(youtube, "Qt Widgets and More", "Lots of tips and tricks for a widget developer",
        "https://www.youtube.com/playlist?list=PL6CJYn40gN6gf-G-o6syFwGrtq3kItEqI");
    add(youtube, "Introduction to Qt / QML", "Video training series on QML",
        "https://www.youtube.com/playlist?list=PL6CJYn40gN6gf-G-o6syFwGrtq3kItEqI");
    add(youtube, "Introduction to Qt Widgets", "Video training series on Qt Widget",
        "https://www.youtube.com/playlist?list=PL6CJYn40gN6iFcTyItvnE5nOmJR8qk_7o");
    add(youtube, "Solutions for Styling Qt Widgets",
        "Different solutions for changing the visual (and interaction) style of Qt widgets",
        "https://www.youtube.com/watch?v=nHFG68rr5kI");

    auto blogs = new QStandardItem("Blogs");
    blogs->setData("https://www.kdab.com/category/blogs/", URLRole);
    blogs->setFlags(blogs->flags() & ~Qt::ItemIsEditable);
    root->appendRow(blogs);

    add(blogs, "10 Tips to Make Your QML Code Faster and More Maintainable",
        "Modernize your code for fun and profit",
        "https://www.kdab.com/10-tips-to-make-your-qml-code-faster-and-more-maintainable");
    add(blogs, "Choosing a Screen for Your Embedded Product", "What to consider?",
        "https://www.kdab.com/choosing-a-screen-for-your-embedded-product");
    add(blogs, "Six Tips for Maximizing Desktop Screen Potential",
        "Six considerations for managing the screen in your desktop application",
        "https://www.kdab.com/six-tips-for-maximizing-desktop-screen-potential");

    auto tree = new QTreeView;
    tree->setAttribute(Qt::WA_DeleteOnClose);
    tree->setModel(model);
    tree->expand(model->indexFromItem(youtube));

    QObject::connect(tree, &QAbstractItemView::doubleClicked, [&](const QModelIndex &index) {
        auto url = index.data(URLRole).toString();
        if (!url.isEmpty())
            QDesktopServices::openUrl(url);
    });

    tree->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    tree->show();
    tree->resize(800, 600);
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    setupTable();
    setupTree();

    return app.exec();
}
