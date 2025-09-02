#include "GanttChart.hpp"

#include <QMenu>
#include <QMenuBar>

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QPen>
#include <QBrush>

void GanttChart::draw(QGraphicsScene* scene, const std::vector<GanttEntry>& gantt, int numCores) {
    scene->clear();
    int height = 42;
    int scale = 22;
    int leftPad = 100;
    int topPad = 40;

    int makespan = 0;
    for (const auto &e : gantt) makespan = std::max(makespan, e.endTime);

    QPen axisPen(QColor(150,150,150));
    for (int c=0; c<numCores; ++c) {
        int y = topPad + c*(height+12);
        scene->addText(QString("Core %1").arg(c+1))->setPos(8, y + height/2 - 18);
        scene->addLine(leftPad, y+height/2, leftPad + makespan*scale, y+height/2, axisPen);
    }

    for (const auto &e : gantt) {
        int x = leftPad + e.startTime * scale;
        int w = (e.endTime - e.startTime) * scale;
        int y = topPad + e.core * (height + 12);

        QColor col = QColor::fromHsv(((e.pid * 47) % 360), 160, 200);
        auto rect = scene->addRect(x, y, std::max(2,w), height-8, QPen(Qt::black), QBrush(col));
        auto text = scene->addText(QString("P%1").arg(e.pid));
        text->setPos(x + 6, y + 6);
    }
}
