#include "GUI_MainWindow.hpp"
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    GuiMainWindow w;
    w.show();
    return app.exec();
}
