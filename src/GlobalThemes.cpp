#include "GlobalThemes.hpp"
#include <QApplication>
#include <QPalette>
#include <QStyleFactory>
#include <QColor>

QString GlobalThemes::getTheme(ThemeMode mode)
{
    qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette pal = qApp->palette();
    QString style;

    switch (mode) {
    case ThemeMode::Fusion: // light
        pal.setColor(QPalette::Window, QColor(240,240,240));
        pal.setColor(QPalette::WindowText, Qt::black);
        pal.setColor(QPalette::Base, Qt::white);
        pal.setColor(QPalette::AlternateBase, QColor(225,225,225));
        pal.setColor(QPalette::ToolTipBase, Qt::white);
        pal.setColor(QPalette::ToolTipText, Qt::black);
        pal.setColor(QPalette::Text, Qt::black);
        pal.setColor(QPalette::Button, QColor(240,240,240));
        pal.setColor(QPalette::ButtonText, Qt::black);
        pal.setColor(QPalette::BrightText, Qt::red);
        pal.setColor(QPalette::Highlight, QColor(0,109,255));
        pal.setColor(QPalette::HighlightedText, Qt::white);
        style = "QTableWidget, QTableView { gridline-color: #b0b0b0; } "
                "QHeaderView::section { padding: 4px; }";
        break;

    case ThemeMode::DarkFusion: // dark
        pal.setColor(QPalette::Window, QColor(53,53,53));
        pal.setColor(QPalette::WindowText, Qt::white);
        pal.setColor(QPalette::Base, QColor(42,42,42));
        pal.setColor(QPalette::AlternateBase, QColor(66,66,66));
        pal.setColor(QPalette::ToolTipBase, Qt::white);
        pal.setColor(QPalette::ToolTipText, Qt::white);
        pal.setColor(QPalette::Text, Qt::white);
        pal.setColor(QPalette::Button, QColor(53,53,53));
        pal.setColor(QPalette::ButtonText, Qt::white);
        pal.setColor(QPalette::BrightText, Qt::red);
        pal.setColor(QPalette::Highlight, QColor(0,122,204));
        pal.setColor(QPalette::HighlightedText, Qt::black);
        style = "QTableWidget, QTableView { gridline-color: #808080; } "
                "QHeaderView::section { padding: 4px; }";
        break;
    }

    qApp->setPalette(pal);
    qApp->setStyleSheet(style);

     // palette handles everything, no return value required as such
    return {};
}
