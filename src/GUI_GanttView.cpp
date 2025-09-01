#include "GUI_GanttView.hpp"

GuiGanttView::GuiGanttView(QWidget* parent) : QGraphicsView(parent) {
    scene = new QGraphicsScene(this);
    setScene(scene);
}
