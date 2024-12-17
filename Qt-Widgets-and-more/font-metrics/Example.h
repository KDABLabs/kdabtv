#pragma once

#include <QWidget>
#include <memory>

namespace Ui {
class Example;
}

class Example : public QWidget
{
    Q_OBJECT

public:
    Example(QWidget *parent = nullptr);
    ~Example();

protected:
    void paintEvent(QPaintEvent *) override;
    void wheelEvent(QWheelEvent *) override;

private:
    enum Mode {
        HorizontalAdvance = 1,
        BoundingRect,
        AdjustedBoundingRect,
        AdjustedBoundingRectAccordingToBearing,
        PainterBoundingRect,
        JustAddSome,
        TightBoundaryBox,
        UsingPointAPI,
        UsingPointAPITight,
        NumberOfModes = UsingPointAPITight,
    };
    void draw(QPainter *painter, Mode);
    void nextStep(int delta);
    void drawGrid(QPainter *painter);
    void drawPoint(QPainter *painter, const QPointF &pos, const QColor &color);
    void setItalic(QPainter *painter, bool italic);

    std::unique_ptr<Ui::Example> ui;
    int m_step = 1;
};
