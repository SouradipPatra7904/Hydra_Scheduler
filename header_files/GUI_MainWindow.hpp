#ifndef GUIMAINWINDOW_HPP
#define GUIMAINWINDOW_HPP

#include <QMainWindow>
#include <QComboBox>
#include <QSpinBox>
#include <QTableWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QAction>

#include <QMenu>
#include <QMenuBar>

#include "Scheduler.hpp"
#include "GUI_GanttView.hpp"

class GuiMainWindow : public QMainWindow {
    Q_OBJECT
public:
    GuiMainWindow(QWidget* parent = nullptr);

private slots:
    void startSimulation();
    void setLightTheme();
    void setDarkTheme();

private:
    // Controls
    QComboBox* algoBox;
    QSpinBox* coreBox;
    QSpinBox* quantumBox;
    QSpinBox* procCountBox;
    QTableWidget* procTable;
    QTextEdit* outputArea;
    GuiGanttView* ganttView;
    QPushButton* startBtn;

    // Menu actions
    QAction* actLight;
    QAction* actDark;

    void buildMenus();
    void setupUi();
    void loadDefaultRows(int count);
};

#endif
