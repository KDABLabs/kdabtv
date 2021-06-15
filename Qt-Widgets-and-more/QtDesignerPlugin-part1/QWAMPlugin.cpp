/* MIT License

Copyright (C) 2021 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "QWAMPlugin.h"

QString QWAMPlugin::toolTip() const
{
    return {};
}

QString QWAMPlugin::whatsThis() const
{
    return {};
}

QIcon QWAMPlugin::icon() const
{
    return {};
}

bool QWAMPlugin::isContainer() const
{
    return false;
}

QWAMPlugin::QWAMPlugin(QString group, QString name, QString includeFile, Factory factory)
    : m_group(std::move(group))
    , m_name(std::move(name))
    , m_includeFile(std::move(includeFile))
    , m_factory(std::move(factory))
{
}

QString QWAMPlugin::group() const
{
    return m_group;
}

QString QWAMPlugin::name() const
{
    return m_name;
}

QString QWAMPlugin::includeFile() const
{
    return m_includeFile;
}

QWidget *QWAMPlugin::createWidget(QWidget *parent)
{
    return m_factory(parent);
}

bool QWAM_isInitialized = false;

bool QWAMPlugin::isInitialized() const
{
    return QWAM_isInitialized;
}

void QWAMPlugin::initialize(QDesignerFormEditorInterface *core)
{
    Q_UNUSED(core);
    QWAM_isInitialized = true;
    // Something like: SystemSettings::setProvideFakeData(true);
}
