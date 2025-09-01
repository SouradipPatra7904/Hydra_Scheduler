#ifndef GANTTCHART_HPP
#define GANTTCHART_HPP

#include <vector>
#include <mutex>
#include <string>

#ifdef USE_GUI
#include <SFML/Graphics.hpp>
#endif

// A segment on a core's timeline
struct Segment {
    int pid;    // -1 for idle
    int start;  // wall-clock start time
    int end;    // wall-clock end time (exclusive)
};

class GanttChart {
public:
    explicit GanttChart(int numCores);

    // record execution on a specific core
    void add(int coreId, int pid, int startTime, int endTime);

    // ASCII view
    void displayASCII(int makespan, int timeScale = 1) const;

#ifdef USE_GUI
    // Draws a GUI representation for all cores into the provided window.
    // `pxPerUnit` controls horizontal scaling. `rowH` controls row height per core.
    void displayGUI(sf::RenderWindow& window, int pxPerUnit = 12, int rowH = 34) const;
#endif

private:
    int cores;
    std::vector<std::vector<Segment>> perCore; // perCore[coreId] = segments
};

#endif
