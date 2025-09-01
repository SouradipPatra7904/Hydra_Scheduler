#ifndef GUIGANTTVIEW_HPP
#define GUIGANTTVIEW_HPP

#include <QGraphicsView>
#include <QGraphicsScene>

class GuiGanttView : public QGraphicsView {
    Q_OBJECT
public:
    GuiGanttView(QWidget* parent = nullptr);
    QGraphicsScene* scene;
};

#endif
