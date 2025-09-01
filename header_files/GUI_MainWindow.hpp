#ifndef GUIMAINWINDOW_HPP
#define GUIMAINWINDOW_HPP

#include <QMainWindow>
#include <QComboBox>
#include <QSpinBox>
#include <QTableWidget>
#include <QTextEdit>
#include <QPushButton>
#include "Scheduler.hpp"
#include "GUI_GanttView.hpp"

class GuiMainWindow : public QMainWindow {
    Q_OBJECT

public:
    GuiMainWindow(QWidget* parent = nullptr);

private slots:
    void startSimulation();

private:
    QComboBox* algoBox;
    QSpinBox* coreBox;
    QSpinBox* quantumBox;
    QSpinBox* procCountBox;
    QTableWidget* procTable;
    QTextEdit* outputArea;
    GuiGanttView* ganttView;
    QPushButton* startBtn;
};

#endif
