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
#include "GlobalThemes.hpp"

// Main window: consistent with current Scheduler/GuiGanttView APIs
class GuiMainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit GuiMainWindow(QWidget* parent = nullptr);

private slots:
    void startSimulation();
    void setTheme(GlobalThemes::ThemeMode mode, bool animate = true);

private:
    void setupUi();
    void buildMenus();
    void loadDefaultRows(int count);

    // --- UI elements ---
    QComboBox*   algoBox{nullptr};
    QSpinBox*    coreBox{nullptr};
    QSpinBox*    quantumBox{nullptr};
    QSpinBox*    procCountBox{nullptr};
    QTableWidget* procTable{nullptr};
    QPushButton*  startBtn{nullptr};
    QTextEdit*    outputArea{nullptr};
    GuiGanttView* ganttView{nullptr};

    // --- Menu actions ---
    QAction* actFusion{nullptr};
    QAction* actDarkFusion{nullptr};
};

#endif // GUIMAINWINDOW_HPP
