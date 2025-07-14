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

class CountryDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    QWidget* createEditor ( QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index ) const override
    {
        Q_UNUSED( option )
        Q_UNUSED( index )
        auto editor = new QComboBox( parent );
        //editor->installEventFilter(this); // already done by QItemDelegate
        return editor;
    }
    void setEditorData( QWidget* editor, const QModelIndex& index ) const override
    {
        auto combo = static_cast<QComboBox*>( editor );
        combo->addItems( countries() );
        int idx = CountryDelegate::countries().indexOf( index.data( Qt::DisplayRole ).toString() );
        combo->setCurrentIndex( idx );
    }
    void setModelData( QWidget * editor, QAbstractItemModel* model, const QModelIndex& index ) const override
    {
        auto combo = static_cast<QComboBox*>( editor );
        model->setData( index, combo->currentText() );
    }

    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem& option, const QModelIndex& /*index*/ ) const override
    {
        QSize cellSize = option.rect.size();
        QSize editorSizeHint = editor->sizeHint();
        QSize editorSize( qMax( cellSize.width(), editorSizeHint.width() ), qMax(cellSize.height(), editorSizeHint.height() ));
        QSize delta = editorSize - cellSize;
        QPoint pos = option.rect.topLeft() - QPoint(delta.width()/2, delta.height()/2);

        int x = std::clamp(pos.x(), 0, editor->parentWidget()->width() - editorSize.width());
        int y = std::clamp(pos.y(), 0, editor->parentWidget()->height() - editorSize.height());

        editor->setGeometry( QRect( QPoint(x,y), editorSize ) );
    }

    // Qt takes care of handling "Return" for us, but let's modify that to edit the next item automatically
    bool eventFilter( QObject* obj, QEvent* event ) override
    {
        if ( event->type() == QEvent::KeyPress &&
             static_cast<QKeyEvent*>(event)->key() == Qt::Key_Return ) {
            emit commitData( static_cast<QWidget*>(obj) );
            emit closeEditor( static_cast<QWidget*>(obj), EditNextItem );
            return false;
        }
        // Handle other keys, like Esc.
        return QStyledItemDelegate::eventFilter( obj, event );
    }

    static QStringList countries()
    {
        QStringList countries;
        countries << "Denmark" << "Sweden" << "Norway" << "USA" << "Germany"
                  << "Poland" << "Iceland" << "Holland" << "Great Britain" << "Ireland" << "Scotland";
        return countries;
    }
};

int main( int argc, char** argv ) {
    QApplication app( argc, argv );

    QList<int> populations;
    populations << 5432 << 9001 << 4593 << 295734 << 82431 << 38635 << 296 << 16407 << 60441 << 4015 << 5062;

    const QStringList countryList = CountryDelegate::countries();

    QStandardItemModel model( 11, 2 );
    for ( int row = 0; row < 11; ++row ) {
        model.setData( model.index( row, 0, QModelIndex() ), countryList[row] );
        model.setData( model.index( row, 1, QModelIndex() ), populations[row] );
        model.setData( model.index( row, 1, QModelIndex() ), Qt::AlignRight, Qt::TextAlignmentRole );
    }
    model.setHeaderData( 0, Qt::Horizontal, "Country" );
    model.setHeaderData( 1, Qt::Horizontal, "Population" );

    auto list = new QListView;
    list->setAttribute(Qt::WA_DeleteOnClose);
    list->setWindowTitle( "QListView" );
    list->setModel( &model );
    CountryDelegate listDelegate;
    list->setItemDelegateForColumn( 0, &listDelegate );
    list->show();

    auto table = new QTableView;
    table->setAttribute(Qt::WA_DeleteOnClose);
    table->setWindowTitle( "QTableView" );
    table->setModel( &model );
    CountryDelegate tableDelegate;
    table->setItemDelegateForColumn( 0, &tableDelegate );
    table->show();

    auto tree = new QTreeView;
    tree->setAttribute(Qt::WA_DeleteOnClose);
    tree->setWindowTitle( "QTreeView" );
    tree->setModel( &model );
    CountryDelegate treeDelegate;
    tree->setItemDelegateForColumn( 0, &treeDelegate );
    tree->show();

    return app.exec();
}

#include "main.moc"
