#ifndef GUIGANTTVIEW_HPP
#define GUIGANTTVIEW_HPP

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>

#include <QMenu>
#include <QMenuBar>

#include <vector>

#include "Scheduler.hpp"   // ✅ bring full GanttEntry definition

struct GanttEntry; // from Scheduler.hpp

class GuiGanttView : public QGraphicsView {
    Q_OBJECT
public:
    explicit GuiGanttView(QWidget* parent = nullptr);

    void clearScene();
    void drawStatic(const std::vector<GanttEntry>& gantt, int numCores);
    void drawAnimated(const std::vector<GanttEntry>& gantt, int numCores, int makespan, int msPerUnit = 60);

private:
    QGraphicsScene* m_scene;
    QTimer m_timer;
    int m_time = 0;
    int m_makespan = 0;
    int m_msPerUnit = 60;
    int m_numCores = 1;

    std::vector<GanttEntry> entries;   // ✅ now legal, since GanttEntry is complete
    // helpers
    void drawFrame(int showUpToTime);
    void drawAxis(int makespan, int pxPerUnit, int rowH, int leftPad, int topPad);
};

#endif
