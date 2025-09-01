#include "GanttChart.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>

GanttChart::GanttChart(int numCores) : cores(numCores), perCore(numCores) {}

void GanttChart::add(int coreId, int pid, int startTime, int endTime) {
    if (coreId < 0 || coreId >= cores) return;
    if (!perCore[coreId].empty()) {
        // coalesce adjacent identical pid segments for cleanliness
        Segment& last = perCore[coreId].back();
        if (last.pid == pid && last.end == startTime) {
            last.end = endTime;
            return;
        }
    }
    perCore[coreId].push_back({pid, startTime, endTime});
}

void GanttChart::displayASCII(int makespan, int timeScale) const {
    std::cout << "\n=== ASCII Gantt Chart ===\n";
    for (int c = 0; c < cores; ++c) {
        std::cout << "Core " << (c+1) << ": ";
        int t = 0;
        for (const auto& seg : perCore[c]) {
            // idle gap
            if (seg.start > t) {
                int gap = (seg.start - t) / timeScale;
                for (int i = 0; i < gap; ++i) std::cout << '.';
                t = seg.start;
            }
            int width = (seg.end - seg.start) / timeScale;
            if (seg.pid < 0) {
                for (int i = 0; i < width; ++i) std::cout << '_';
            } else {
                std::cout << '|';
                for (int i = 0; i < std::max(1, width-2); ++i) std::cout << '=';
                std::cout << 'P' << seg.pid << '|';
            }
            t = seg.end;
        }
        if (t < makespan) {
            for (int i = 0; i < (makespan - t)/timeScale; ++i) std::cout << '.';
        }
        std::cout << "\n";
    }

    std::cout << "Time: ";
    for (int t = 0; t <= makespan; t += timeScale)
        std::cout << std::setw(2) << t << ' ';
    std::cout << "\n";
}

#ifdef USE_GUI
void GanttChart::displayGUI(sf::RenderWindow& window, int pxPerUnit, int rowH) const {
    window.clear(sf::Color(30, 30, 36));

    const int margin = 40;
    int width = window.getSize().x;
    int y = margin;

    // axis
    sf::RectangleShape axis(sf::Vector2f(width - 2*margin, 1));
    axis.setFillColor(sf::Color(180,180,180));

    // colors per PID (simple hash)
    auto colorFor = [](int pid)->sf::Color{
        if (pid < 0) return sf::Color(80,80,80);
        unsigned x = static_cast<unsigned>(pid) * 2654435761U;
        return sf::Color(60 + (x&0x9F), 60 + ((x>>8)&0x9F), 60 + ((x>>16)&0x9F));
    };

    // draw each core timeline
    for (int c = 0; c < cores; ++c) {
        // baseline
        axis.setPosition(margin, y + rowH/2);
        window.draw(axis);

        // label
        sf::Font font;
        // Try default font; if not available, skip labels silently
        if (font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
            sf::Text label("Core " + std::to_string(c+1), font, 14);
            label.setFillColor(sf::Color(220,220,230));
            label.setPosition(6, y + rowH/2 - 10);
            window.draw(label);
        }

        // draw segments
        for (const auto& seg : perCore[c]) {
            int x1 = margin + seg.start * pxPerUnit;
            int x2 = margin + seg.end   * pxPerUnit;
            sf::RectangleShape rect(sf::Vector2f(std::max(1, x2 - x1), rowH - 8));
            rect.setPosition(x1, y + 4);
            rect.setFillColor(colorFor(seg.pid));
            rect.setOutlineColor(sf::Color::Black);
            rect.setOutlineThickness(1.f);
            window.draw(rect);

            // PID text
            if (seg.pid >= 0 && font.getInfo().family != "") {
                sf::Text pidTxt("P" + std::to_string(seg.pid), font, 12);
                pidTxt.setFillColor(sf::Color::Black);
                pidTxt.setPosition(x1 + 4, y + 6);
                window.draw(pidTxt);
            }
        }

        y += rowH + 14;
    }

    window.display();
}
#endif
