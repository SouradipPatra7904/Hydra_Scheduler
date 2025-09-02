#ifndef GANTTCHART_HPP
#define GANTTCHART_HPP

#include "Scheduler.hpp"
#include <QGraphicsScene>
#include <QMenu>
#include <QMenuBar>

class GanttChart {
public:
    // Kept for compatibility: static immediate draw (used by older code)
    static void draw(QGraphicsScene* scene, const std::vector<GanttEntry>& gantt, int numCores);
};

#endif
