/****************************************************************************
**
** This file is part of the Oxygen2 project.
**
** SPDX-FileCopyrightText: 2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
**
** SPDX-License-Identifier: MIT
**
****************************************************************************/

/*************************************************************************
 *
 * Copyright (c) 2013-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

#include "teststyle.h"
#include "checkboxstylehelper.h"
#include "progressbarstylehelper.h"
#include "pushbuttonstylehelper.h"

#include <QCheckBox>
#include <QPushButton>
#include <QStyleOptionButton>

TestStyle::TestStyle()
    : super()
    , mPushButtonStyleHelper(new PushButtonStyleHelper)
    , mCheckBoxStyleHelper(new CheckBoxStyleHelper)
    , mProgressBarStyleHelper(new ProgressBarStyleHelper)
{
}

void TestStyle::drawPrimitive(PrimitiveElement pe, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    switch (pe) {
    case PE_IndicatorCheckBox:
        if (const auto *optionButton = qstyleoption_cast<const QStyleOptionButton *>(option)) {
            mCheckBoxStyleHelper->draw(this, optionButton, painter, widget);
        }
        return;
    case PE_FrameFocusRect:
        // nothing, we don't want focus rects
        break;
    default:
        super::drawPrimitive(pe, option, painter, widget);
        break;
    }
}

int TestStyle::pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const
{
    switch (metric) {
    case PM_IndicatorHeight: // checkboxes
    case PM_IndicatorWidth: // checkboxes
        return mCheckBoxStyleHelper->indicatorSize();

    case PM_ButtonShiftHorizontal:
    case PM_ButtonShiftVertical:
        return 0; // no shift

    default:
        return super::pixelMetric(metric, option, widget);
    }
}

void TestStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    switch (element) {
    case CE_PushButton:
        // The default implementation calls CE_PushButtonBevel, CE_PushButtonLabel
        // and PE_FrameFocusRect (which we reimplement to nothing).
        QCommonStyle::drawControl(element, option, painter, widget);
        return;
    case CE_PushButtonBevel:
        // Draw button shape (background and border). This one we'll fully implement ourselves.
        if (const auto *optionButton = qstyleoption_cast<const QStyleOptionButton *>(option)) {
            mPushButtonStyleHelper->drawButtonShape(optionButton, painter, widget);
        }
        return;
    case CE_PushButtonLabel:
        // Draw button text, icon (and menu indicator)
        // We just want to call the base class, with an adjusted palette
        if (const auto *optionButton = qstyleoption_cast<const QStyleOptionButton *>(option)) {
            QStyleOptionButton copy = *optionButton;
            mPushButtonStyleHelper->adjustTextPalette(&copy);
            QCommonStyle::drawControl(element, &copy, painter, widget);
        }
        return;

    case CE_RadioButton: // simply calls PE_IndicatorRadioButton, CE_RadioButtonLabel (and focus rect)
    case CE_RadioButtonLabel:
    case CE_CheckBox: // simply calls PE_IndicatorCheckBox, CE_CheckBoxLabel (and focus rect)
    case CE_CheckBoxLabel:
        QCommonStyle::drawControl(element, option, painter, widget);
        return;

    case CE_ProgressBar: // main entry point
        // calls CE_ProgressBarGroove, CE_ProgressBarContents and CE_ProgressBarLabel
        QCommonStyle::drawControl(element, option, painter, widget);
        return;
    case CE_ProgressBarGroove:
        if (const auto *progressBarOption = qstyleoption_cast<const QStyleOptionProgressBar *>(option)) {
            mProgressBarStyleHelper->drawGroove(progressBarOption, painter, widget);
        }
        break;
    case CE_ProgressBarContents:
        if (const auto *progressBarOption = qstyleoption_cast<const QStyleOptionProgressBar *>(option)) {
            mProgressBarStyleHelper->drawContents(progressBarOption, painter, widget);
        }
        break;
    case CE_ProgressBarLabel:
        if (const auto *progressBarOption = qstyleoption_cast<const QStyleOptionProgressBar *>(option)) {
            mProgressBarStyleHelper->drawText(progressBarOption, painter, widget);
        }
        return;

    default:
        super::drawControl(element, option, painter, widget);
    }
}

void TestStyle::polish(QWidget *w)
{
    if (qobject_cast<QPushButton *>(w) || qobject_cast<QCheckBox *>(w)) {
        w->setAttribute(Qt::WA_Hover);
    }
    super::polish(w);
}

bool TestStyle::eventFilter(QObject *obj, QEvent *event)
{
    return super::eventFilter(obj, event);
}

PushButtonStyleHelper *TestStyle::pushButtonStyleHelper() const
{
    return mPushButtonStyleHelper.get();
}

int TestStyle::styleHint(StyleHint stylehint, const QStyleOption *option, const QWidget *widget,
                         QStyleHintReturn *returnData) const
{
    switch (stylehint) {
    case SH_DialogButtonBox_ButtonsHaveIcons:
        return 0;
    default:
        break;
    }

    return super::styleHint(stylehint, option, widget, returnData);
}

QSize TestStyle::sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &contentsSize,
                                  const QWidget *widget) const
{
    switch (type) {
    case CT_PushButton:
        if (const auto *buttonOption = qstyleoption_cast<const QStyleOptionButton *>(option)) {
            return mPushButtonStyleHelper->sizeFromContents(buttonOption, contentsSize, widget);
        }
        break;
    case CT_RadioButton:
    case CT_CheckBox:
        return QCommonStyle::sizeFromContents(type, option, contentsSize, widget);

    default:
        break;
    }
    return super::sizeFromContents(type, option, contentsSize, widget);
}

QRect TestStyle::subElementRect(SubElement subElement, const QStyleOption *option, const QWidget *widget) const
{
    switch (subElement) {
    case SE_ProgressBarGroove:
    case SE_ProgressBarContents:
    case SE_ProgressBarLabel:
        if (const auto *progressBarOption = qstyleoption_cast<const QStyleOptionProgressBar *>(option)) {
            return mProgressBarStyleHelper->subElementRect(subElement, progressBarOption, widget);
        }
        break;
    default:
        break;
    }
    return super::subElementRect(subElement, option, widget);
}

void TestStyle::drawComplexControl(ComplexControl complexControl, const QStyleOptionComplex *option, QPainter *painter,
                                   const QWidget *widget) const
{
    switch (complexControl) {
    default:
        super::drawComplexControl(complexControl, option, painter, widget);
    }
}
