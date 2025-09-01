#include "GUI_MainWindow.hpp"
#include "GanttChart.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QHeaderView>

GuiMainWindow::GuiMainWindow(QWidget* parent) : QMainWindow(parent) {
    QWidget* central = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(central);

    QHBoxLayout* optsLayout = new QHBoxLayout();
    algoBox = new QComboBox();
    algoBox->addItems({"FCFS", "SJF", "PRIORITY", "RR"});

    coreBox = new QSpinBox(); coreBox->setRange(1, 8); coreBox->setValue(2);
    quantumBox = new QSpinBox(); quantumBox->setRange(1, 10); quantumBox->setValue(2);
    procCountBox = new QSpinBox(); procCountBox->setRange(1, 15); procCountBox->setValue(5);

    optsLayout->addWidget(new QLabel("Algorithm:")); optsLayout->addWidget(algoBox);
    optsLayout->addWidget(new QLabel("Cores:")); optsLayout->addWidget(coreBox);
    optsLayout->addWidget(new QLabel("Quantum:")); optsLayout->addWidget(quantumBox);
    optsLayout->addWidget(new QLabel("Processes:")); optsLayout->addWidget(procCountBox);

    procTable = new QTableWidget(5, 4);
    procTable->setHorizontalHeaderLabels({"PID", "Arrival", "Burst", "Priority"});
    procTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    startBtn = new QPushButton("Start Simulation");
    outputArea = new QTextEdit(); outputArea->setReadOnly(true);

    ganttView = new GuiGanttView();

    mainLayout->addLayout(optsLayout);
    mainLayout->addWidget(procTable);
    mainLayout->addWidget(startBtn);
    mainLayout->addWidget(outputArea);
    mainLayout->addWidget(ganttView);

    setCentralWidget(central);

    connect(startBtn, &QPushButton::clicked, this, &GuiMainWindow::startSimulation);
}

void GuiMainWindow::startSimulation() {
    int algoIndex = algoBox->currentIndex();
    Algorithm algo = static_cast<Algorithm>(algoIndex);
    int cores = coreBox->value();
    int tq = quantumBox->value();

    Scheduler sched(cores, algo, tq);

    int rowCount = procTable->rowCount();
    for (int i = 0; i < rowCount; i++) {
        bool ok1, ok2, ok3, ok4;
        int pid = procTable->item(i, 0) ? procTable->item(i, 0)->text().toInt(&ok1) : i+1;
        int at  = procTable->item(i, 1) ? procTable->item(i, 1)->text().toInt(&ok2) : 0;
        int bt  = procTable->item(i, 2) ? procTable->item(i, 2)->text().toInt(&ok3) : 1;
        int pr  = procTable->item(i, 3) ? procTable->item(i, 3)->text().toInt(&ok4) : 0;

        sched.addProcess(Process(pid, at, bt, pr));
    }

    sched.run();

    QString output;
    output += QString::fromStdString(sched.getMetrics()) + "\n";
    output += QString::fromStdString(sched.getAsciiGantt());
    outputArea->setText(output);

    GanttChart::draw(ganttView->scene, sched.getGantt(), cores);
}
