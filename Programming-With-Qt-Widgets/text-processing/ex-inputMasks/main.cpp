/*************************************************************************
 *
 * Copyright (c) 2008-2010, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2010-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include <QFont>
#include<QtWidgets>
#include <QDebug>

class IPValidator :public QValidator
{
public:
    explicit IPValidator( QLineEdit* parent ) :QValidator( parent ) {}
protected:
    State validate ( QString& input, int& ) const override
    {
        for ( int pos = 0; pos<15;pos+=4 ) {
            bool ok1;
            int i = QStringView{input}.mid(pos,1).toInt(&ok1);
            bool ok2;
            int j = QStringView{input}.mid(pos+1,1).toInt(&ok2);
            bool ok3;
            int k = QStringView{input}.mid(pos+2,1).toInt(&ok3);

            if ( ( ok1 && i > 2 ) ||
                 ( ok1 && ok2 && i == 2 && j > 5 ) ||
                 (ok1 && ok2 && ok3 && i*100+j*10+k > 255 ) )
                return Invalid;
            if (!ok1 || !ok2 || !ok3)
                return Intermediate;
        }
        return Acceptable;
    }
};

int main( int argc, char** argv ) {
    QApplication app( argc, argv );

    QFont font("Monospace");
    font.setStyleHint(QFont::TypeWriter);

    auto ipLabel = new QLabel( "IP Address:" );
    auto ipEdit = new QLineEdit;
    ipEdit->setFont(font);
    ipEdit->setInputMask("000.000.000.000;_");
    ipEdit->setValidator( new IPValidator( ipEdit ) );
    QObject::connect(ipEdit, &QLineEdit::returnPressed, [ipEdit]  {
        qDebug() << "The IP Address: " << ipEdit->text();
    });

    auto isoLabel = new QLabel("ISO Date:" );
    auto isoEdit = new QLineEdit;
    isoEdit->setInputMask( "0000-00-00" );
    isoEdit->setFont(font);

    auto licenseLabel = new QLabel("License Number:" );
    auto licenseEdit = new QLineEdit;
    licenseEdit->setInputMask( ">AAAAA-AAAAA-AAAAA-AAAAA-AAAAA;#" );
    licenseEdit->setFont(font);

    auto top = new QWidget;
    auto layout = new QGridLayout( top );
    layout->addWidget( ipLabel, 0, 0 );
    layout->addWidget( ipEdit, 0, 1 );
    layout->addWidget( isoLabel, 1, 0 );
    layout->addWidget( isoEdit, 1, 1 );
    layout->addWidget( licenseLabel, 2, 0 );
    layout->addWidget( licenseEdit, 2, 1 );

    top->show();
    return app.exec();
}
