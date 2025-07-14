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

class Test :public QMainWindow
{
    Q_OBJECT
public:
    explicit Test( QWidget* parent = nullptr )
        :QMainWindow( parent )
    {
        m_currentLabel = new QLabel;
        statusBar()->addWidget( m_currentLabel );

        auto view = new QTableView;
        setCentralWidget( view );

        m_model = new QStandardItemModel( 10, 5, this );
        view->setModel( m_model );

        QItemSelectionModel* selectionModel = view->selectionModel();
        connect( selectionModel, &QItemSelectionModel::currentChanged,
                 this, &Test::currentItemChanged );
        connect( selectionModel, &QItemSelectionModel::selectionChanged,
                 this, &Test::updateSelection );

        QItemSelection selection1( m_model->index( 0, 0, QModelIndex() ), m_model->index( 2, 2, QModelIndex() ) );
        selectionModel->select(  selection1, QItemSelectionModel::Select );


        QItemSelection selection2( m_model->index( 6, 0, QModelIndex() ), m_model->index( 8, 0, QModelIndex() ) );
        selectionModel->select(  selection2, QItemSelectionModel::Select | QItemSelectionModel::Rows );

        QItemSelection selection3( m_model->index( 0, 1, QModelIndex() ), m_model->index( 0, 1, QModelIndex() ) );
        selectionModel->select(  selection3,
                                 QItemSelectionModel::Columns  | QItemSelectionModel::Toggle );
}

private:
    void currentItemChanged(  const QModelIndex& current )
    {
        m_currentLabel->setText( QString( "row: %1 col: %2" ).arg( current.row() ).arg( current.column() ) );
    }

    void updateSelection( const QItemSelection& selected, const QItemSelection& deselected )
    {
        QModelIndexList items = selected.indexes();
        for( const QModelIndex & index : std::as_const(items) )
            m_model->setData( index, QString( "(%1,%2)" ).arg( index.row() ).arg( index.column() ) );

        items = deselected.indexes();
        for( const QModelIndex& index : std::as_const(items) )
            m_model->setData( index, "" );
    }


private:
    QLabel* m_currentLabel;
    QStandardItemModel* m_model;
};

int main( int argc, char** argv ) {
    QApplication app( argc, argv );

    Test test;
    test.resize( 800, 600 );
    test.show();

    return app.exec();
}

#include "main.moc"
