#include <QApplication>
#include <QSettings>
#include <QMenu>
#include <QMenuBar>

#include "GUI_MainWindow.hpp"
#include "GlobalThemes.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Identify app for QSettings (org/app can be anything you prefer)
    QCoreApplication::setOrganizationName("LabTools");
    QCoreApplication::setOrganizationDomain("lab.local");
    QCoreApplication::setApplicationName("Hydra_Scheduler");

    // Load persisted theme (default = light)
    QSettings settings;
    const QString theme = settings.value("ui/theme", "light").toString();
    if (theme == "dark") {
        app.setStyleSheet(THEME_DARK);
    } else {
        app.setStyleSheet(THEME_LIGHT);
    }

    GuiMainWindow w;
    // Bigger startup window
    w.resize(1280, 840);
    w.show();

    return app.exec();
}
