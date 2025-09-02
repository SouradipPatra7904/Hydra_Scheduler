#include "GUI_GanttView.hpp"
#include "Scheduler.hpp" // for GanttEntry
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QPen>
#include <QBrush>

#include <QMenu>
#include <QMenuBar>

GuiGanttView::GuiGanttView(QWidget* parent) : QGraphicsView(parent), m_scene(new QGraphicsScene(this)) {
    setScene(m_scene);
    setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    setObjectName("GanttView");

    connect(&m_timer, &QTimer::timeout, this, [this](){
        if (m_time > m_makespan) { m_timer.stop(); return; }
        drawFrame(m_time);
        m_time++;
    });
}

void GuiGanttView::clearScene() {
    m_scene->clear();
    m_time = 0;
    m_makespan = 0;
    entries.clear();
}

void GuiGanttView::drawStatic(const std::vector<GanttEntry>& gantt, int numCores) {
    clearScene();
    entries = gantt;
    m_numCores = numCores;

    int makespan = 0;
    for (const auto &e : gantt) makespan = std::max(makespan, e.endTime);
    drawFrame(makespan);
}

void GuiGanttView::drawAnimated(const std::vector<GanttEntry>& gantt, int numCores, int makespan, int msPerUnit) {
    clearScene();
    entries = gantt;
    m_numCores = numCores;
    m_makespan = makespan;
    m_msPerUnit = msPerUnit;

    // First frame (t=0) then start ticking
    drawFrame(0);
    m_time = 1;
    m_timer.start(m_msPerUnit);
}

void GuiGanttView::drawAxis(int makespan, int pxPerUnit, int rowH, int leftPad, int topPad) {
    QPen axisPen(QColor(150,150,150));
    QFont tickFont; tickFont.setPointSizeF(9.0);

    for (int c=0; c<m_numCores; ++c) {
        int y = topPad + c * (rowH + 12);
        // baseline
        m_scene->addLine(leftPad, y + rowH/2, leftPad + makespan*pxPerUnit, y + rowH/2, axisPen);

        // label
        auto t = m_scene->addText(QString("Core %1").arg(c+1));
        t->setPos(8, y + rowH/2 - 18);
    }

    // time ticks every 5 units
    for (int t=0; t<=makespan; t+=5) {
        int x = leftPad + t * pxPerUnit;
        m_scene->addLine(x, topPad - 8, x, topPad + m_numCores*(rowH+12), axisPen);
        auto lbl = m_scene->addText(QString::number(t));
        lbl->setPos(x - 6, topPad - 24);
        lbl->setDefaultTextColor(QColor(120,120,120));
    }
}

void GuiGanttView::drawFrame(int showUpToTime) {
    m_scene->clear();

    const int pxPerUnit = 22;
    const int rowH = 42;
    const int leftPad = 100;
    const int topPad = 40;

    int makespan = std::max(m_makespan, showUpToTime);
    drawAxis(makespan, pxPerUnit, rowH, leftPad, topPad);

    // playhead
    QPen playPen(QColor(0, 140, 255, 180)); playPen.setWidth(2);

    // Draw segments up to showUpToTime
    for (const auto &e : entries) {
        int y = topPad + e.core * (rowH + 12);
        int start = e.startTime;
        int end   = e.endTime;
        if (start > showUpToTime) continue;

        int visibleEnd = std::min(end, showUpToTime);
        if (visibleEnd <= start) continue;

        int x = leftPad + start * pxPerUnit;
        int w = std::max(2, (visibleEnd - start) * pxPerUnit);

        QColor col = QColor::fromHsv(((e.pid * 47) % 360), 160, 200);
        QPen pen(Qt::black); pen.setWidth(1);
        QBrush brush(col);

        auto rect = m_scene->addRect(x, y, w, rowH-8, pen, brush);
        auto text = m_scene->addText(QString("P%1 (%2-%3)")
                                     .arg(e.pid).arg(start).arg(std::min(end, showUpToTime)));
        text->setPos(x + 6, y + 6);
    }

    // draw playhead line
    int playX = leftPad + showUpToTime * pxPerUnit;
    m_scene->addLine(playX, topPad - 10, playX, topPad + m_numCores*(rowH+12), playPen);

    // Fit view once (on first frames). Avoid continuous fit to keep user zoom.
    if (showUpToTime <= 1) {
        fitInView(m_scene->itemsBoundingRect().adjusted(-20, -20, 20, 20), Qt::KeepAspectRatio);
    }
}
