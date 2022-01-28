#include "DoNotShowAgainMessageBox.h"
#include <QCheckBox>
#include <QPushButton>
#include <QSettings>
#include <memory>

Q_DECLARE_METATYPE(QMessageBox::StandardButton);

QMessageBox::StandardButton
DoNotShowAgainMesageBox::information(const QString &key, QWidget *parent, const QString &title,
                                     const QString &text, StandardButtons buttons,
                                     StandardButton defaultButton)
{
    DoNotShowAgainMesageBox box(key, parent);
    box.setWindowTitle(title);
    box.setText(text);
    box.setStandardButtons(buttons);
    box.setDefaultButton(defaultButton);

    return box.execute();
}

QMessageBox::StandardButton DoNotShowAgainMesageBox::execute()

{
    QSettings settings("KDAB", "QWAM");
    settings.beginGroup("DoNotShowAgain");
    if (settings.contains(m_key))
        return settings.value(m_key).value<StandardButton>();

    exec();

    auto button = standardButton(clickedButton());
    if (checkBox()->isChecked())
        settings.setValue(m_key, button);

    return button;
}

void DoNotShowAgainMesageBox::clearAll()
{
    QSettings settings("KDAB", "QWAM");
    settings.remove("DoNotShowAgain");
}

DoNotShowAgainMesageBox::DoNotShowAgainMesageBox(const QString &key, QWidget *parent)
    : QMessageBox(parent)
    , m_key(key)
{
    auto *cb = new QCheckBox("Do not show again");
    setCheckBox(cb);
}
