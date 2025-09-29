/*************************************************************************
 *
 * Copyright (c) 2010-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include <QtWidgets>

class HelpFilter :public QObject {
    Q_OBJECT

public:
    explicit HelpFilter( QStatusBar* bar, QObject *parent = nullptr )
        : QObject(parent), _bar(bar)
    {
    }

    void registerHelp( QObject* obj, const QString& text )
    {
        _messages.insert( obj, text );
        connect( obj, SIGNAL( destroyed ( QObject* ) ), this, SLOT( unregister( QObject* ) ) );
    }

public slots:
    void unregister( QObject* obj )
    {
        _messages.remove( obj );
    }


protected:
    bool eventFilter( QObject* receiver, QEvent* event ) override
    {
        if ( event->type() == QEvent::Enter )
            _bar->showMessage( _messages.value(receiver), 5000 );
        else if ( event->type() == QEvent::Leave )
            _bar->clearMessage( );

        return false;
    }

private:
    QMap<QObject*,QString> _messages;
    QStatusBar* _bar;
};

int main( int argc, char**argv)
{
    QApplication app(argc, argv);

    auto win = new QMainWindow();
    auto help = new HelpFilter( win->statusBar() );
    app.installEventFilter( help );

    auto box = new QCheckBox( "CheckBox" );
    help->registerHelp( box, "Text for checkbox" );

    auto edit= new QLineEdit;
    help->registerHelp( edit, "Text for lineEdit" );

    auto top = new QWidget;
    win->setCentralWidget( top );

    auto layout = new QVBoxLayout( top );
    layout->addWidget( box );
    layout->addWidget( edit );

    win->show();

    return app.exec();
}

#include "main.moc"
