#include "GanttChart.hpp"
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QBrush>
#include <QPen>

void GanttChart::draw(QGraphicsScene* scene, const std::vector<GanttEntry>& gantt, int numCores) {
    scene->clear();
    int height = 50;
    int scale = 20;

    for (const auto& e : gantt) {
        int x = e.startTime * scale;
        int w = (e.endTime - e.startTime) * scale;
        int y = e.core * height;

        auto rect = scene->addRect(x, y, w, height, QPen(Qt::black), QBrush(Qt::cyan));
        auto text = scene->addText(QString("P%1").arg(e.pid));
        text->setPos(x + w/4, y + height/4);
    }
}
