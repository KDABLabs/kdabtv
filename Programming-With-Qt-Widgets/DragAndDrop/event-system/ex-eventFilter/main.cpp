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
public:
  explicit HelpFilter( QStatusBar* bar, const QString& txt, QObject* parent )
      : QObject( parent )
  {
    _bar = bar;
    _txt = txt;
  }

private:
  QStatusBar* _bar;
  QString _txt;

protected:
  bool eventFilter( QObject* /*receiver*/, QEvent* event )  override
  {
    if ( event->type() == QEvent::Enter ) {
      _bar->showMessage( _txt, 5000 );
    }
    else if ( event->type() == QEvent::Leave ) {
      _bar->clearMessage( );
    }

    return false;
  }
};


int main( int argc, char**argv)
{
  QApplication app(argc, argv);

  auto win = new QMainWindow();

  auto box = new QCheckBox( "CheckBox" );
  auto boxFilter = new HelpFilter( win->statusBar(), "Text for checkbox", win );
  box->installEventFilter( boxFilter );

  auto edit= new QLineEdit;
  auto editFilter = new HelpFilter( win->statusBar(), "Text for lineEdit", win );
  edit->installEventFilter( editFilter );

  auto top = new QWidget;
  win->setCentralWidget( top );

  auto layout = new QVBoxLayout( top );
  layout->addWidget( box );
  layout->addWidget( edit );

  win->show();

  return app.exec();
}
