#include <QDialog>
#include <QVariant>
#include <kdalgorithms.h>

class NewCode : public QDialog
{
    void setupFocus()
    {
        const auto wantFocus = [](QWidget *widget) {
            return widget->property("WantsFocus").isValid() && widget->isVisible();
        };

        // Used to sort by position
        const auto byPosition = [](QWidget *left, QWidget *right) {
            auto leftMapped = left->mapToGlobal(QPoint(0, 0));
            auto rightMapped = right->mapToGlobal(QPoint(0, 0));
            return std::tuple(leftMapped.y(), leftMapped.x())
                < std::tuple(rightMapped.y(), rightMapped.x());
        };

        QList<QWidget *> allChildren = findChildren<QWidget *>();
        QList<QWidget *> focusCandidates =
            kdalgorithms::filtered(std::move(allChildren), wantFocus);

        if (focusCandidates.isEmpty())
            return;

        kdalgorithms::sort(focusCandidates, byPosition);

        // now setup tab order.
        for (int i = 0, numberOfItems = focusCandidates.count(); i < numberOfItems; ++i) {
            setTabOrder(focusCandidates.at(i), focusCandidates.at((i + 1) % numberOfItems));
        }

        // Finally set focus on the first list select
        auto widget = kdalgorithms::get_first_match(focusCandidates, [](QWidget *widget) {
            return widget->property("FocusCandidate").isValid() && widget->isVisible();
        });
        if (widget)
            (*widget)->setFocus();
    }
};
