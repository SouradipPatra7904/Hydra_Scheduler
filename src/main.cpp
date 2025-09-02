#include <QApplication>
#include "GUI_MainWindow.hpp"
#include "GlobalThemes.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Apply dark theme by default
    GlobalThemes::getTheme(GlobalThemes::ThemeMode::DarkFusion);

    GuiMainWindow w;
    w.show();

    return app.exec();
}
