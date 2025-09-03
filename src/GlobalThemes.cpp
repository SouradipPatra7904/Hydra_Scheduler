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
    case ThemeMode::Fusion: // Material Light
        pal.setColor(QPalette::Window, QColor("#00e599"));
        pal.setColor(QPalette::WindowText, QColor("#212121"));
        pal.setColor(QPalette::Base, QColor("#ffffff"));
        pal.setColor(QPalette::AlternateBase, QColor("#f5f5f5"));
        pal.setColor(QPalette::ToolTipBase, QColor("#ffffff"));
        pal.setColor(QPalette::ToolTipText, QColor("#212121"));
        pal.setColor(QPalette::Text, QColor("#212121"));
        pal.setColor(QPalette::Button, QColor("#e0e0e0"));
        pal.setColor(QPalette::ButtonText, QColor("#212121"));
        pal.setColor(QPalette::BrightText, QColor("#d32f2f"));
        pal.setColor(QPalette::Highlight, QColor("#2962ff"));
        pal.setColor(QPalette::HighlightedText, QColor("#ffffff"));

        style = R"(
            /* === Tables === */
            QTableWidget, QTableView {
                gridline-color: #bdbdbd;
                border: 1px solid #bdbdbd;
            }
            QHeaderView::section {
                padding: 6px;
                background: #e0e0e0;
                color: #212121;
                font-weight: bold;
                border: 1px solid #bdbdbd;
            }

            /* === Inner Window Borders === */
            QFrame, QGroupBox, QDialog {
                background-clip: padding;
            }

            /* === PushButtons === */
            QPushButton {
                background-color: #212121;
                color:  #00e599;
                border-radius: 4px;
                padding: 6px 12px;
            }
            QPushButton:hover { background-color: #555555;}
            QPushButton:pressed { background-color: #2c2c2c; }

            /* === SpinBox Arrows (Light, theme aware) === */
            QSpinBox::up-button {
                subcontrol-origin: border;
                subcontrol-position: top right;
                width: 20px; height: 12px;
                border: 1px solid #bdbdbd; 
                background: #e0e0e0;
            }
            QSpinBox::down-button {
                subcontrol-origin: border;
                subcontrol-position: bottom right;
                width: 20px; height: 12px;
                border: 1px solid #bdbdbd;
                background: #e0e0e0;
            }
            QSpinBox::up-arrow {
                width: 0; height: 0;
                border-left: 6px solid transparent;
                border-right: 6px solid transparent;
                border-bottom: 8px solid #212121;
            }
            QSpinBox::down-arrow {
                width: 0; height: 0;
                border-left: 6px solid transparent;
                border-right: 6px solid transparent;
                border-top: 8px solid #212121;
            }

            /* === Scrollbars (Light, no arrows, fixed margins) === */
            QScrollBar:vertical {
                border: none;
                background: #f0f0f0;
                width: 10px;
                margin: 0px 0px 0px 0px;
            }
            QScrollBar::handle:vertical {
                background: #000000;
                min-height: 20px;
            }
            QScrollBar::handle:vertical:hover { background: #00e599; }

            QScrollBar:horizontal {
                border: none;
                background: #f0f0f0;
                height: 10px;
                margin: 0px 0px 0px 0px;
            }
            QScrollBar::handle:horizontal {
                background: #000000;
                min-width: 20px;
            }
            QScrollBar::handle:horizontal:hover { background: #00e599; }
            
            /* REMOVE ARROWS COMPLETELY */
            QScrollBar::add-line:vertical,
            QScrollBar::sub-line:vertical {
                border: none;
                background: none;
                height: 0;
            }

            QScrollBar::add-page:vertical,
            QScrollBar::sub-page:vertical {
                background: none;
            }  

            QScrollBar::add-line:horizontal,
            QScrollBar::sub-line:horizontal {
                border: none;
                background: none;
                width: 0;
            }

            QScrollBar::add-page:horizontal,
            QScrollBar::sub-page:horizontal {
            background: none;
            }
        )";
        break;

    case ThemeMode::DarkFusion: // Material Dark
        pal.setColor(QPalette::Window, QColor("#121212"));
        pal.setColor(QPalette::WindowText, QColor("#eaeaea"));
        pal.setColor(QPalette::Base, QColor("#1e1e1e"));
        pal.setColor(QPalette::AlternateBase, QColor("#2c2c2c"));
        pal.setColor(QPalette::ToolTipBase, QColor("#333333"));
        pal.setColor(QPalette::ToolTipText, QColor("#eaeaea"));
        pal.setColor(QPalette::Text, QColor("#eaeaea"));
        pal.setColor(QPalette::Button, QColor("#2c2c2c"));
        pal.setColor(QPalette::ButtonText, QColor("#eaeaea"));
        pal.setColor(QPalette::BrightText, QColor("#ff5252"));
        pal.setColor(QPalette::Highlight, QColor("#00e599"));
        pal.setColor(QPalette::HighlightedText, QColor("#000000"));

        style = R"(
            /* === Tables === */
            QTableWidget, QTableView {
                gridline-color: #555555;
                border: 1px solid #555555;
            }
            QHeaderView::section {
                padding: 6px;
                background: #2c2c2c;
                color: #eaeaea;
                font-weight: bold;
                border: 1px solid #555555;
            }

            /* === Inner Window Borders === */
            QFrame, QGroupBox, QDialog {
                background-clip: padding;
            }

            /* === PushButtons === */
            QPushButton {
                background-color: #00e599;
                color: #000000;
                border-radius: 4px;
                padding: 6px 12px;
            }
            QPushButton:hover { background-color: #1de9b6; }
            QPushButton:pressed { background-color: #00bfa5; }

            /* === SpinBox Arrows (Dark, theme aware) === */
            QSpinBox::up-button {
                subcontrol-origin: border;
                subcontrol-position: top right;
                width: 20px; height: 12px;
                border: 1px solid #555555; 
                background: #2c2c2c;
            }
            QSpinBox::down-button {
                subcontrol-origin: border;
                subcontrol-position: bottom right;
                width: 20px; height: 12px;
                border: 1px solid #555555; 
                background: #2c2c2c;
            }
            QSpinBox::up-arrow {
                width: 0; height: 0;
                border-left: 6px solid transparent;
                border-right: 6px solid transparent;
                border-bottom: 8px solid #00e599;
            }
            QSpinBox::down-arrow {
                width: 0; height: 0;
                border-left: 6px solid transparent;
                border-right: 6px solid transparent;
                border-top: 8px solid #00e599;
            }

            /* === Scrollbars (Dark, no arrows, fixed margins) === */
            QScrollBar:vertical {
                border: none;
                background: #1e1e1e;
                width: 10px;
                margin: 0px 0px 0px 0px;
            }
            QScrollBar::handle:vertical {
                background: #00e599;
                min-height: 20px;
            }
            QScrollBar::handle:vertical:hover { background: #00e599; }

            QScrollBar:horizontal {
                border: none;
                background: #1e1e1e;
                height: 10px;
                margin: 0px 0px 0px 0px;
            }
            QScrollBar::handle:horizontal {
                background: #00e599;
                min-width: 20px;
            }
            QScrollBar::handle:horizontal:hover { background: #00e599; }

            /* REMOVE ARROWS COMPLETELY */
            QScrollBar::add-line:vertical,
            QScrollBar::sub-line:vertical {
                border: none;
                background: none;
                height: 0;
            }

            QScrollBar::add-page:vertical,
            QScrollBar::sub-page:vertical {
                background: none;
            }

            QScrollBar::add-line:horizontal,
            QScrollBar::sub-line:horizontal {
                border: none;
                background: none;
                width: 0;
            }

            QScrollBar::add-page:horizontal,
            QScrollBar::sub-page:horizontal {
            background: none;
            }
        )";
        break;
    }

    qApp->setPalette(pal);
    qApp->setStyleSheet(style);

    return {};
}
