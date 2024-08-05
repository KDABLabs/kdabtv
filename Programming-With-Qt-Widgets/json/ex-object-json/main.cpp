/*************************************************************************
 *
 * Copyright (c) 2012-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QByteArray>
#include <QDebug>

int main()
{
    // How this example is structured...
    // 1. Build up an object-based QJsonDocument
    // 2. Write it out to disk
    // 3. Read it back and perform various validity and value checks

    // 1. Build up an object-based QJsonDocument
    // Appending basic types...
    QJsonObject object;
    QJsonValue media(QStringLiteral("Film"));
    object.insert(QStringLiteral("Media"), media);
    QJsonValue name(QStringLiteral("Monty Python's Life of Brian"));
    object.insert(QStringLiteral("Name"),name);
    QJsonValue releaseYear(1979);
    object.insert(QStringLiteral("Release_Year"), releaseYear);
    QJsonValue isPartOfFranchise(true);
    object.insert(QStringLiteral("Is_Part_of_Franchise"), isPartOfFranchise);

    // QJsonArrays can also be inserted into an object...
    QJsonArray array;
    QJsonValue cast1(QStringLiteral("Graham Chapman"));
    array.append(cast1);
    QJsonValue cast2(QStringLiteral("John Cleese"));
    array.append(cast2);
    QJsonValue cast3(QStringLiteral("Terry Gilliam"));
    array.append(cast3);
    QJsonValue cast4(QStringLiteral("Eric Idle"));
    array.append(cast4);
    QJsonValue cast5(QStringLiteral("Terry Jones"));
    array.append(cast5);
    QJsonValue cast6(QStringLiteral("Michael Palin"));
    array.append(cast6);
    object.insert(QStringLiteral("Cast"), array);

    // Back to appending basic types...
    QJsonValue valueString2(QStringLiteral("Here is another string"));
    object.insert(QStringLiteral("String"), valueString2);
    QJsonValue valueBool2(false);
    object.insert(QStringLiteral("Bool"), valueBool2);

    QJsonDocument document;

    // Create an object based QJsonDocument...
    document.setObject(object);

    // 2. Write it out to disk
    // Write it out to disk so that we can read it in again...
    QFile file(QStringLiteral("data.json"));
    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    file.write(document.toJson());
    file.close();

    qDebug() << "JSON document written to disk...";
    qDebug() << document.toJson();

    // 3. Read it back and perform various validity and value checks
    // Read JSON document from disk...
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray jsonData = file.readAll();
    file.close();

    // Some basic error checking...
    QJsonParseError jsonError;
    QJsonDocument document2 = QJsonDocument::fromJson(jsonData, &jsonError);
    if (jsonError.error != QJsonParseError::NoError)
        qWarning() << "Failed to parse JSON document from disk"
                    << jsonError.errorString() << "at:" << jsonError.offset;
    if (document2.isNull())
        qWarning() << "Parsed JSON document appears to be empty";
    if (!document2.isObject())
        qWarning() << "Did not find expected object based JSON document";

    // Verify some elements...
    if (document2.object()["Bool"].type() != QJsonValue::Bool ||
        document2.object()["Bool"] != false)
        qWarning() << "Either type or value of element did not match that expected";

    if (document2.object()["Cast"].type() != QJsonValue::Array ||
        document2.object()["Cast"].toArray().at(3).type() != QJsonValue::String ||
        document2.object()["Cast"].toArray().at(3) != QStringLiteral("Eric Idle"))
        qWarning() << "Either type or value of element did not match that expected";

    return 0;
}

