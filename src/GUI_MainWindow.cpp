#include "GUI_MainWindow.hpp"
#include "GanttChart.hpp"
#include "GlobalThemes.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <QMenuBar>
#include <QApplication>
#include <QSettings>

#include <QMenu>
#include <QMenuBar>

GuiMainWindow::GuiMainWindow(QWidget* parent) : QMainWindow(parent) {
    setupUi();
    buildMenus();
}

void GuiMainWindow::buildMenus() {
    QMenu* view = menuBar()->addMenu("View");
    actLight = view->addAction("Light Theme");
    actDark  = view->addAction("Dark Theme");
    connect(actLight, &QAction::triggered, this, &GuiMainWindow::setLightTheme);
    connect(actDark,  &QAction::triggered, this, &GuiMainWindow::setDarkTheme);
}

void GuiMainWindow::setupUi() {
    QWidget* central = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(central);

    QHBoxLayout* optsLayout = new QHBoxLayout();
    algoBox = new QComboBox();
    algoBox->addItems({"FCFS", "SJF", "PRIORITY", "ROUND_ROBIN"});

    coreBox = new QSpinBox(); coreBox->setRange(1, 16); coreBox->setValue(4);
    quantumBox = new QSpinBox(); quantumBox->setRange(1, 50); quantumBox->setValue(3);
    procCountBox = new QSpinBox(); procCountBox->setRange(1, 15); procCountBox->setValue(5);

    optsLayout->addWidget(new QLabel("Algorithm:")); optsLayout->addWidget(algoBox);
    optsLayout->addWidget(new QLabel("Cores:"));     optsLayout->addWidget(coreBox);
    optsLayout->addWidget(new QLabel("Quantum:"));   optsLayout->addWidget(quantumBox);
    optsLayout->addWidget(new QLabel("Processes:")); optsLayout->addWidget(procCountBox);

    procTable = new QTableWidget(procCountBox->value(), 4);
    procTable->setObjectName("ProcTable");
    procTable->setHorizontalHeaderLabels({"PID", "Arrival", "Burst", "Priority"});
    procTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    loadDefaultRows(procCountBox->value());
    connect(procCountBox, &QSpinBox::valueChanged, this, [this](int v){
        procTable->setRowCount(v);
        loadDefaultRows(v);
    });

    startBtn = new QPushButton("Start Simulation");

    outputArea = new QTextEdit();
    outputArea->setReadOnly(true);

    ganttView = new GuiGanttView();
    ganttView->setObjectName("GanttView"); // stylesheet hook

    mainLayout->addLayout(optsLayout);
    mainLayout->addWidget(procTable);
    mainLayout->addWidget(startBtn);
    mainLayout->addWidget(new QLabel("Output / ASCII:"));
    mainLayout->addWidget(outputArea, 1);
    mainLayout->addWidget(new QLabel("Gantt:"));
    mainLayout->addWidget(ganttView, 2);

    setCentralWidget(central);
    connect(startBtn, &QPushButton::clicked, this, &GuiMainWindow::startSimulation);
}

void GuiMainWindow::loadDefaultRows(int count) {
    for (int r=0; r<count; ++r) {
        if (!procTable->item(r,0)) procTable->setItem(r,0, new QTableWidgetItem(QString::number(r+1)));
        if (!procTable->item(r,1)) procTable->setItem(r,1, new QTableWidgetItem(QString::number(r)));
        if (!procTable->item(r,2)) procTable->setItem(r,2, new QTableWidgetItem(QString::number(5)));
        if (!procTable->item(r,3)) procTable->setItem(r,3, new QTableWidgetItem(QString::number(1)));
    }
}

void GuiMainWindow::startSimulation() {
    // Allow multiple runs: clear output + scene
    outputArea->clear();
    ganttView->clearScene();

    // Build scheduler
    Algorithm algo = static_cast<Algorithm>(algoBox->currentIndex());
    int cores = coreBox->value();
    int tq = quantumBox->value();

    Scheduler sched(cores, algo, tq);

    // Read processes from table
    const int rows = procTable->rowCount();
    for (int i=0; i<rows; ++i) {
        auto getCell = [&](int c)->int {
            auto *it = procTable->item(i, c);
            bool ok=false;
            int v = it ? it->text().toInt(&ok) : 0;
            return ok ? v : 0;
        };
        int pid = getCell(0); if (pid<=0) pid = i+1;
        int at  = getCell(1);
        int bt  = std::max(1, getCell(2));
        int pr  = getCell(3);
        sched.addProcess(Process(pid, at, bt, pr));
    }

    sched.run();

    // Text metrics + ASCII
    QString out;
    out += QString::fromStdString(sched.getMetrics()) + "\n";
    out += QString::fromStdString(sched.getAsciiGantt());
    outputArea->setText(out);

    // Animated Gantt: 60ms per time unit (adjust to taste)
    const auto &g = sched.getGantt();
    int makespan = 0;
    for (const auto &e : g) makespan = std::max(makespan, e.endTime);

    ganttView->drawAnimated(g, cores, makespan, /*msPerUnit*/ 60);
}

void GuiMainWindow::setLightTheme() {
    qApp->setStyleSheet(THEME_LIGHT);
    QSettings().setValue("ui/theme", "light");
}
void GuiMainWindow::setDarkTheme() {
    qApp->setStyleSheet(THEME_DARK);
    QSettings().setValue("ui/theme", "dark");
}
