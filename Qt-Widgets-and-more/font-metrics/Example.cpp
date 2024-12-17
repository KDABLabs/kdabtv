#include "Example.h"
#include "ui_Example.h"
#include <QFontMetricsF>
#include <QPainter>
#include <QWheelEvent>

namespace {
constexpr auto SCALE = 20;
}

Example::Example(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Example)
{
    ui->setupUi(this);
    connect(ui->text, &QLineEdit::textChanged, this, qOverload<>(&Example::update));
    connect(ui->prev, &QToolButton::clicked, this, [this] { nextStep(-1); });
    connect(ui->next, &QToolButton::clicked, this, [this] { nextStep(+1); });
    ui->text->setText("f");
    nextStep(0);
}

Example::~Example() = default;

void Example::wheelEvent(QWheelEvent *event)
{
    nextStep(event->angleDelta().y() > 0 ? -1 : 1);
}

void Example::setItalic(QPainter *painter, bool italic)
{
    QFont font = painter->font();
    font.setItalic(italic);
    painter->setFont(font);
}

void Example::drawGrid(QPainter *painter)
{
    auto setPen = [&](int x) {
        if (x % 5 == 0)
            painter->setPen(QPen(Qt::gray, 0, Qt::SolidLine));
        else
            painter->setPen(QPen(Qt::lightGray, 0, Qt::DotLine));
    };

    // Notice the grid is translated, so the end of the for loops are not correct, but it doesn't
    // really matter for this example.

    for (int x = 0; x < width(); x += 1) {
        setPen(x);
        painter->drawLine(x, 0, x, height() / SCALE);
    }

    for (int y = 0; y < height(); y += 1) {
        setPen(y);
        painter->drawLine(0, y, width() / SCALE, y);
    }
}

void Example::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    const int x = ui->layout->contentsMargins().left();
    const int y = ui->description->y() + ui->description->height() + ui->layout->spacing();
    painter.translate(x, y);
    painter.scale(SCALE, SCALE);

    drawGrid(&painter);

    if (ui->text->text().isEmpty())
        return;

    auto mode = static_cast<Mode>(m_step);

    painter.translate(5, 15);
    setItalic(&painter, false);
    draw(&painter, mode);

    int delta = QFontMetricsF(painter.font()).boundingRect(ui->text->text()).width() + 6;
    painter.translate(delta, 0);
    setItalic(&painter, true);
    draw(&painter, mode);
}

void Example::drawPoint(QPainter *painter, const QPointF &pos, const QColor &color)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawEllipse(pos, 10.0 / SCALE, 10.0 / SCALE);

    setItalic(painter, false);

    painter->translate(pos);
    painter->scale(2.0 / SCALE, 2.0 / SCALE);
    painter->translate(-pos);

    painter->translate(5, -5);
    painter->setPen(color);
    painter->drawText(pos, QString("(%1,%2)").arg(pos.x()).arg(pos.y()));
    painter->restore();
}

void Example::draw(QPainter *painter, Mode mode)
{
    drawPoint(painter, QPointF(0, 0), Qt::green);

    QRectF rect;
    QFontMetricsF fm(painter->font());
    QString text = ui->text->text();

    auto drawBoundary = [&] {
        painter->setPen(QPen(Qt::red, 3.0 / SCALE, Qt::SolidLine));
        painter->drawRect(rect);
        painter->setPen(QPen(Qt::green, 3.0 / SCALE, Qt::SolidLine));
        painter->drawRect(QRectF(0, 0, rect.width(), rect.height()));
        painter->setPen(Qt::black);
    };

    switch (mode) {
    case HorizontalAdvance: {
        rect = QRectF(0, 0, fm.horizontalAdvance(text), fm.height());
        drawBoundary();
        painter->drawText(rect, Qt::TextDontClip, text);
        break;
    }
    case BoundingRect: {
        rect = fm.boundingRect(text);
        drawBoundary();
        painter->drawText(rect, Qt::TextDontClip, text);
        drawPoint(painter, rect.topLeft(), Qt::red);
        break;
    }
    case AdjustedBoundingRect: {
        rect = fm.boundingRect(text).translated(-fm.boundingRect(text).topLeft());
        drawBoundary();
        painter->drawText(rect, Qt::TextDontClip, text);
        break;
    }
    case AdjustedBoundingRectAccordingToBearing: {
        rect = fm.boundingRect(text).translated(-fm.leftBearing(text.at(0)), fm.ascent());
        drawBoundary();
        painter->drawText(rect, Qt::TextDontClip, text);
        break;
    }
    case PainterBoundingRect: {
        rect = painter->boundingRect(QRectF(), text);
        drawBoundary();
        painter->drawText(rect, Qt::TextDontClip, text);
        break;
    }
    case JustAddSome: {
        rect = painter->boundingRect(QRectF(), text).adjusted(0, 0, 4, 0);
        drawBoundary();
        painter->drawText(rect.translated(2, 0), Qt::TextDontClip, text);
        break;
    }
    case TightBoundaryBox: {
        rect = fm.tightBoundingRect(text);
        drawBoundary();
        painter->drawText(rect, Qt::TextDontClip, text);
        drawPoint(painter, rect.topLeft(), Qt::red);
        break;
    }
    case UsingPointAPI: {
        const auto boundingRect = fm.boundingRect(text);
        rect = QRectF(0, 0, boundingRect.width(), boundingRect.height());
        drawBoundary();
        painter->drawText(-boundingRect.topLeft(), text);
        drawPoint(painter, -boundingRect.topLeft(), Qt::blue);
        break;
    }
    case UsingPointAPITight: {
        const auto boundingRect = fm.tightBoundingRect(text);
        rect = QRectF(0, 0, boundingRect.width(), boundingRect.height());
        drawBoundary();
        painter->drawText(-boundingRect.topLeft(), text);
        drawPoint(painter, -boundingRect.topLeft(), Qt::blue);
        break;
    }
    }
}

void Example::nextStep(int delta)
{
    if (m_step + delta < 1 || m_step + delta > NumberOfModes)
        return;

    m_step += delta;

    auto setTitle = [this](const QString &title) { ui->description->setText(title); };

    ui->stepLabel->setText(QString("Step #%1").arg(m_step));
    switch (static_cast<Mode>(m_step)) {
    case HorizontalAdvance:
        setTitle(
            "The goal is simple, paint the text at (0,0) as the topmost corner, and draw a box "
            "around it.\n"
            "Trying to get the width using QFontMetricsF::width() results in a warning in Qt 5.15, "
            "telling us to use QFontMetricsF::advance() instead. width() doesn't even exists in Qt "
            "6.\n"
            "The problem: The width is too narrow.");
        break;
    case BoundingRect:
        setTitle(
            "QFontMetricsF::boundingRect() sounds promising, as the docs says that it holds the "
            "pixels painted.\nThe green box is the rect if placed at (0,0), while the red is the "
            "actual rect returned.\n"
            "The problem: The size is right, but the position is off.");
        break;
    case AdjustedBoundingRect:
        setTitle("This is the boundingRect() translated by the negative offset\n"
                 "The problem: Some letters are cut off (e.g. f, j, and M).");
        break;
    case AdjustedBoundingRectAccordingToBearing:
        setTitle("This is the boundingRect() translated according to the bearing and ascent.\n"
                 "The problem: Still cut off.");
        break;
    case PainterBoundingRect:
        setTitle("QPainter also has a boundingRect() method, let's try this.\n"
                 "The problem: Close but no cigar, it still cuts off some letters.");
        break;
    case JustAddSome:
        setTitle("HACK ALERT: Let's just add a bit of space.\n"
                 "The problem: The first word in the line above.");
        break;
    case TightBoundaryBox:
        setTitle("How about QFontMetricsF::tightBoundingRect(), does that work?\n"
                 "No.");
        break;
    case UsingPointAPI:
        setTitle(
            "Way more reading documentation....\n"
            "Turns out that the QFontMetricsF method return two things: a size and a position. "
            "The latter is to be given to the other version of drawText.\n"
            "The problem: I will never remember this....");
        break;
    case UsingPointAPITight:
        setTitle("Finally let's check if it also works with tightBoundingRect()");
        break;
    }
    update();
    ui->prev->setEnabled(m_step > 1);
    ui->next->setEnabled(m_step < NumberOfModes);
}
