#include "GUI_MainWindow.hpp"
#include "Process.hpp"
#include "Scheduler.hpp"
#include "GanttChart.hpp"
#include "GUI_GanttView.hpp"

#include <QApplication>
#include <QActionGroup>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QMessageBox>

GuiMainWindow::GuiMainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setupUi();
    buildMenus();

    setMinimumSize(1200, 950);
}


/* ---------- UI ---------- */
void GuiMainWindow::setupUi()
{
    QWidget* central = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(central);

    // --- Controls Row ---
    auto* controlsLayout = new QHBoxLayout();

    algoBox = new QComboBox();
    // Match the enum Algorithm exactly
    algoBox->addItems({"FCFS", "SJF", "PRIORITY", "ROUND_ROBIN"});
    algoBox->setCurrentIndex(0);

    coreBox = new QSpinBox();
    coreBox->setRange(1, 32);
    coreBox->setValue(4);

    quantumBox = new QSpinBox();
    quantumBox->setRange(1, 1000);
    quantumBox->setValue(3);

    procCountBox = new QSpinBox();
    procCountBox->setRange(1, 200);
    procCountBox->setValue(5);

    startBtn = new QPushButton("Start Simulation");
    connect(startBtn, &QPushButton::clicked, this, &GuiMainWindow::startSimulation);

    // Add labels for clarity
    controlsLayout->addWidget(new QLabel("Algorithm:"));
    controlsLayout->addWidget(algoBox);
    controlsLayout->addWidget(new QLabel("Cores:"));
    controlsLayout->addWidget(coreBox);
    controlsLayout->addWidget(new QLabel("Quantum:"));
    controlsLayout->addWidget(quantumBox);
    controlsLayout->addWidget(new QLabel("Processes:"));
    controlsLayout->addWidget(procCountBox);
    controlsLayout->addStretch(1);
    controlsLayout->addWidget(startBtn);

    mainLayout->addLayout(controlsLayout);

    // --- Process Table ---
    // Use 4 columns: PID, Arrival, Burst, Priority — matches previous working code
    procTable = new QTableWidget(procCountBox->value(), 4);
    procTable->setObjectName("ProcTable");
    procTable->setHorizontalHeaderLabels({"PID", "Arrival", "Burst", "Priority"});
    procTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    loadDefaultRows(procCountBox->value());

    connect(procCountBox, &QSpinBox::valueChanged, this, [this](int v){
        procTable->setRowCount(v);
        loadDefaultRows(v);
    });

    mainLayout->addWidget(procTable);

    // --- Output Area ---
    outputArea = new QTextEdit();
    outputArea->setReadOnly(true);
    mainLayout->addWidget(new QLabel("Output / ASCII:"));
    mainLayout->addWidget(outputArea, 1);

    // --- Gantt Chart ---
    ganttView = new GuiGanttView();
    ganttView->setObjectName("GanttView"); // stylesheet hook
    mainLayout->addWidget(new QLabel("Gantt:"));
    mainLayout->addWidget(ganttView, 2);

    setCentralWidget(central);
}

void GuiMainWindow::buildMenus()
{
    //QMenu* themeMenu = menuBar()->addMenu("Themes");

    /*
    menuBar()->setStyleSheet(
        "QMenuBar::item { "
        "   border: 1px solid #666666; "
        "   padding: 4px 8px; "
        "   border-radius: 4px; "
        "} "
        "QMenuBar::item:selected { "
        "   background: #0078d7; "
        "   color: white; "
        "} "
    );
    */
    

    // --- Create the "Themes" menu ---
    QMenu* themeMenu = menuBar()->addMenu("Themes");

    /*
    // --- Dropdown menu styling ---
    themeMenu->setStyleSheet(
        "QMenu { "
        "   border: 1px solid #666666; "
        "   border-radius: 4px; "
        "   padding: 4px; "
        "} "
        "QMenu::item:selected { "
        "   background-color: #0078d7; "
        "   color: white; "
        "} "
    );
    */

    actFusion    = new QAction("Fusion (Light)", this);
    actDarkFusion= new QAction("Dark Fusion", this);

    actFusion->setCheckable(true);
    actDarkFusion->setCheckable(true);

    // not mutually exclusive in UI by default; make them radio buttons if you like
    QActionGroup* themeGroup = new QActionGroup(this);
    themeGroup->setExclusive(true);
    themeGroup->addAction(actFusion);
    themeGroup->addAction(actDarkFusion);

    connect(actFusion, &QAction::triggered, [this]() {
        setTheme(GlobalThemes::ThemeMode::Fusion);
    });
    connect(actDarkFusion, &QAction::triggered, [this]() {
        setTheme(GlobalThemes::ThemeMode::DarkFusion);
    });

    themeMenu->addAction(actFusion);
    themeMenu->addAction(actDarkFusion);

    // Default theme at startup (optional)
    actFusion->setChecked(true);
    setTheme(GlobalThemes::ThemeMode::Fusion, /*animate*/false);
}

void GuiMainWindow::loadDefaultRows(int count)
{
    for (int r = 0; r < count; ++r) {
        if (!procTable->item(r, 0)) procTable->setItem(r, 0, new QTableWidgetItem(QString::number(r+1))); // PID
        if (!procTable->item(r, 1)) procTable->setItem(r, 1, new QTableWidgetItem(QString::number(r)));   // Arrival
        if (!procTable->item(r, 2)) procTable->setItem(r, 2, new QTableWidgetItem(QString::number(5)));   // Burst
        if (!procTable->item(r, 3)) procTable->setItem(r, 3, new QTableWidgetItem(QString::number(1)));   // Priority
    }
}

/* ---------- Simulation ---------- */
void GuiMainWindow::startSimulation()
{
    // clear previous
    outputArea->clear();
    ganttView->clearScene();

    // collect controls
    Algorithm algo = static_cast<Algorithm>(algoBox->currentIndex()); // 0..3 as added
    int cores = coreBox->value();
    int tq    = quantumBox->value();

    Scheduler sched(cores, algo, tq);

    // read processes from table
    const int rows = procTable->rowCount();
    for (int i = 0; i < rows; ++i) {
        auto readInt = [&](int col, int fallback)->int {
            QTableWidgetItem* it = procTable->item(i, col);
            if (!it) return fallback;
            bool ok = false;
            int v = it->text().toInt(&ok);
            return ok ? v : fallback;
        };
        int pid = readInt(0, i+1);
        int at  = readInt(1, i);
        int bt  = std::max(1, readInt(2, 5));
        int pr  = readInt(3, 1);

        sched.addProcess(Process(pid, at, bt, pr));
    }

    // run + report
    sched.run();

    QString metrics = QString::fromStdString(sched.getMetrics());
    QString ascii   = QString::fromStdString(sched.getAsciiGantt());
    outputArea->setPlainText(metrics + "\n" + ascii);

    // draw gantt
    const auto& g = sched.getGantt();
    int makespan = 0;
    for (const auto& e : g) makespan = std::max(makespan, e.endTime);

    ganttView->drawAnimated(g, cores, makespan, /*msPerUnit*/60);
}

/* ---------- Theme ---------- */
void GuiMainWindow::setTheme(GlobalThemes::ThemeMode mode, bool /*animate*/)
{
    GlobalThemes::getTheme(mode); // applies Fusion/DarkFusion palette
    if (actFusion && actDarkFusion) {
        if (mode == GlobalThemes::ThemeMode::Fusion) {
            actFusion->setChecked(true);
        } else {
            actDarkFusion->setChecked(true);
        }
    }
}
