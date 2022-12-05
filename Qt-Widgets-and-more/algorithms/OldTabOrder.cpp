#include <QDialog>
#include <QVariant>

class OldCode : public QDialog
{
    void setupFocus()
    {
        QList<QWidget *> list = findChildren<QWidget *>();
        QList<QWidget *> orderedList;

        // Iterate through all widgets in our dialog.
        for (QObject *obj : list) {
            QWidget *current = static_cast<QWidget *>(obj);
            if (!current->property("WantsFocus").isValid() || !current->isVisible())
                continue;

            int cx = current->mapToGlobal(QPoint(0, 0)).x();
            int cy = current->mapToGlobal(QPoint(0, 0)).y();

            bool inserted = false;
            // Iterate through the ordered list of widgets, and insert the current one, so it is in
            // the right position in the tab chain.
            for (QList<QWidget *>::iterator orderedIt = orderedList.begin();
                 orderedIt != orderedList.end(); ++orderedIt) {
                const QWidget *w = *orderedIt;
                int wx = w->mapToGlobal(QPoint(0, 0)).x();
                int wy = w->mapToGlobal(QPoint(0, 0)).y();

                if (wy > cy || (wy == cy && wx >= cx)) {
                    orderedList.insert(orderedIt, current);
                    inserted = true;
                    break;
                }
            }
            if (!inserted)
                orderedList.append(current);
        }

        // now setup tab order.
        QWidget *prev = nullptr;
        QWidget *first = nullptr;
        for (QWidget *widget : qAsConst(orderedList)) {
            if (prev) {
                setTabOrder(prev, widget);
            } else {
                first = widget;
            }
            prev = widget;
        }

        if (first) {
            setTabOrder(prev, first);
        }

        // Finally set focus on the first list select
        for (QWidget *widget : qAsConst(orderedList)) {
            if (widget->property("FocusCandidate").isValid() && widget->isVisible()) {
                widget->setFocus();
                break;
            }
        }
    }
};
