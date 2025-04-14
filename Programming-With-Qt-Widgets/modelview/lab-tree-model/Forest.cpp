/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "Forest.h"
#include "TreeNode.h"
#include <QFile>
#include <QRegularExpression>
#include <QStack>

TreeNode *Forest::load()
{
    QFile file(":/default.txt");
    bool ok = file.open(QIODevice::ReadOnly);
    Q_ASSERT(ok);
    return load(QString::fromUtf8(file.readAll()).split("\n"));
}

TreeNode *Forest::load(const QStringList &lines)
{
    QStringList rootData{"Title", "Summary"};
    auto result = new TreeNode(rootData, nullptr);

    QStack<TreeNode *> parents;
    QStack<int> indentations;

    parents.push(result);
    indentations.push(0);

    for (const QString &line : lines) {
        static QRegularExpression nonSpaceCharacter("[^ \t]");
        const int indentation = line.indexOf(nonSpaceCharacter);
        const QString lineData = line.mid(indentation).trimmed();

        if (!lineData.isEmpty()) {
            // Read the column data from the rest of the line.
            const QStringList columnData = lineData.split("\t", Qt::SkipEmptyParts);

            if (indentation > indentations.top()) {
                // Increase indentation - means new children
                // The last child of the current parent is now the new parent
                parents.push(parents.last()->child(parents.last()->childCount() - 1));
                indentations.push(indentation);
            } else {
                // If we decrease indentation, we need to pop to the current parent level
                while (indentation < indentations.top()) {
                    parents.pop();
                    indentations.pop();
                }
            }

            // Append a new node to the current parent's list of children.
            parents.top()->appendChild(new TreeNode(columnData, parents.last()));
        }
    }

    return result;
}
