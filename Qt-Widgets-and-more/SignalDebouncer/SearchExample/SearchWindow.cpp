#include "SearchWindow.h"
#include "KDSignalThrottler.h"
#include "ui_SearchWindow.h"
#include <QFile>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include <QTextStream>
#include <QThread>

namespace {
class Filter : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    using QSortFilterProxyModel::QSortFilterProxyModel;
    void setFilterText(const QString &text)
    {
        m_filterText = text;
        invalidateFilter();
    }
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override
    {
        // make it slow on purpose, to emulate a slow source model
        QThread::msleep(1);
        const QString txt = sourceModel()->index(source_row, 0, source_parent).data().toString();
        return txt.contains(m_filterText, Qt::CaseInsensitive);
    }

private:
    QString m_filterText;
};

QStringList readWords(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return QStringList();
    }

    QTextStream in(&file);
    static QRegularExpression regexp(R"(\s+)");
    return in.readAll().split(regexp, Qt::SkipEmptyParts);
}

} // namespace

SearchWindow::SearchWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SearchWindow)
{
    ui->setupUi(this);

    const auto words = readWords(":/text");

    auto model = new QStandardItemModel(words.count(), 1, this);
    int i = 0;
    for (const auto &word : words) {
        model->setItem(i++, 0, new QStandardItem(word));
    }

    auto filter = new Filter(this);
    filter->setSourceModel(model);

#if 1
    connect(ui->lineEdit, &QLineEdit::textChanged, filter, &Filter::setFilterText);
#else
    auto bouncer = new KDToolBox::KDSignalDebouncer(this);
    bouncer->setTimeout(500);
    connect(ui->lineEdit, &QLineEdit::textChanged, bouncer,
            &KDToolBox::KDSignalDebouncer::throttle);
    connect(bouncer, &KDToolBox::KDSignalDebouncer::triggered, filter,
            [filter, this] { filter->setFilterText(ui->lineEdit->text()); });
#endif

    ui->listView->setModel(filter);
}

SearchWindow::~SearchWindow() = default;

#include "SearchWindow.moc"
