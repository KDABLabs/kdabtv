#pragma once

#include <QWidget>
#include <memory>

namespace Ui {
class SearchWindow;
}

class SearchWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SearchWindow(QWidget *parent = nullptr);
    ~SearchWindow();

private:
    std::unique_ptr<Ui::SearchWindow> ui;
};
