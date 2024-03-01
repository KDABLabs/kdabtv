/*************************************************************************
 *
 * Copyright (c) 2008-2010, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2010-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "CountrySelector.h"
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QCompleter>
#include <QCheckBox>
#include <QLineEdit>
#include <QFile>
#include <QTextStream>

CountrySelector::CountrySelector(QWidget *parent)
    : QWidget(parent)
{
    auto grid = new QGridLayout( this );
    grid->setColumnStretch(1,1);
    int row = -1;

    // Completion Mode
    auto label = new QLabel( "Completion Mode");
    m_mode = new QComboBox;
    m_mode->addItem( "Filtered Popup Completion", QCompleter::PopupCompletion );
    m_mode->addItem( "Unfiltered Popup Completion", QCompleter::UnfilteredPopupCompletion );
    m_mode->addItem( "Inline Completion", QCompleter::InlineCompletion );

    grid->addWidget( label, ++row, 0 );
    grid->addWidget( m_mode, row, 1 );
    connect( m_mode, SIGNAL( activated(int) ), this, SLOT( changeComlpetionMode(int) ) );

    // Case Sensitivity
    label = new QLabel( "Case Sensitivity" );
    m_caseSensitivity = new QComboBox;
    m_caseSensitivity->addItem( "Case Sensitive", Qt::CaseSensitive );
    m_caseSensitivity->addItem( "Case Insensitive", Qt::CaseInsensitive );
    connect( m_caseSensitivity, SIGNAL( activated(int) ), this, SLOT( changeCaseSensitivity(int) ) );

    grid->addWidget( label, ++row, 0 );
    grid->addWidget( m_caseSensitivity, row, 1 );


    // Wrap
    m_wrap = new QCheckBox( "Wrap around completions" );
    m_wrap->setChecked(true);
    grid->addWidget( m_wrap, ++row, 0, 1, 2 );


    // Country
    label = new QLabel( "Country");
    auto edit = new QLineEdit;
    m_completer = new QCompleter( countries(), this );
    edit->setCompleter( m_completer );

    grid->addWidget( label, ++row, 0 );
    grid->addWidget( edit, row, 1 );

    connect( m_wrap, &QAbstractButton::clicked, m_completer, &QCompleter::setWrapAround );
}

void CountrySelector::changeComlpetionMode(int index)
{
    m_completer->setCompletionMode( static_cast<QCompleter::CompletionMode>( m_mode->itemData(index).toInt() ) );
}

QStringList CountrySelector::countries()
{
    QFile file( ":/countries.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream stream( &file );
    return stream.readAll().split("\n");
}

void CountrySelector::changeCaseSensitivity(int index)
{
    m_completer->setCaseSensitivity ( static_cast<Qt::CaseSensitivity>( m_caseSensitivity->itemData(index).toInt() ) );
}
