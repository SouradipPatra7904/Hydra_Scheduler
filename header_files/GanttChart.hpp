#ifndef GANTTCHART_HPP
#define GANTTCHART_HPP

#include "Scheduler.hpp"
#include <QGraphicsView>
#include <QGraphicsScene>

class GanttChart {
public:
    static void draw(QGraphicsScene* scene, const std::vector<GanttEntry>& gantt, int numCores);
};

#endif
