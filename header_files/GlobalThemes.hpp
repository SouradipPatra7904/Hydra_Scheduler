#ifndef THEMES_HPP
#define THEMES_HPP

#include <QString>

// Inline SVG icons (white + black arrows for consistency)
inline const char* ARROW_DOWN_LIGHT = "data:image/svg+xml;utf8,<svg xmlns='http://www.w3.org/2000/svg' width='8' height='8' fill='black'><polygon points='0,0 8,0 4,6'/></svg>";
inline const char* ARROW_UP_LIGHT   = "data:image/svg+xml;utf8,<svg xmlns='http://www.w3.org/2000/svg' width='8' height='8' fill='black'><polygon points='0,6 8,6 4,0'/></svg>";

inline const char* ARROW_DOWN_DARK  = "data:image/svg+xml;utf8,<svg xmlns='http://www.w3.org/2000/svg' width='8' height='8' fill='white'><polygon points='0,0 8,0 4,6'/></svg>";
inline const char* ARROW_UP_DARK    = "data:image/svg+xml;utf8,<svg xmlns='http://www.w3.org/2000/svg' width='8' height='8' fill='white'><polygon points='0,6 8,6 4,0'/></svg>";

/* ---------------- LIGHT THEME ---------------- */
inline QString THEME_LIGHT = QString(R"CSS(
/* ---------- Base ---------- */
QWidget {
  background-color: #fafafa;
  color: #222222;
  font-family: "Segoe UI", "Inter", "Noto Sans", sans-serif;
  font-size: 10.5pt;
}

/* ---------- Containers ---------- */
QGroupBox {
  border: 1px solid #e6e6e6;
  border-radius: 10px;
  margin-top: 8px;
}
QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 4px; }

/* ---------- Inputs ---------- */
QLineEdit, QTextEdit, QPlainTextEdit, QComboBox, QSpinBox, QDoubleSpinBox, QTableWidget, QTableView {
  background: #ffffff;
  border: 1px solid #d8d8d8;
  border-radius: 8px;
  selection-background-color: #006dff;
  selection-color: #ffffff;
}
QLineEdit:focus, QTextEdit:focus, QPlainTextEdit:focus, QComboBox:focus, QSpinBox:focus, QDoubleSpinBox:focus, QTableWidget:focus, QTableView:focus {
  border: 1px solid #5798ff;
}

/* SpinBox buttons */
QSpinBox::up-button, QDoubleSpinBox::up-button {
  subcontrol-origin: border;
  subcontrol-position: top right;
  width: 16px;
  border-left: 1px solid #d0d0d0;
  background: transparent;
}
QSpinBox::down-button, QDoubleSpinBox::down-button {
  subcontrol-origin: border;
  subcontrol-position: bottom right;
  width: 16px;
  border-left: 1px solid #d0d0d0;
  background: transparent;
}
QSpinBox::up-arrow, QDoubleSpinBox::up-arrow {
  image: url()CSS" + QString(ARROW_UP_LIGHT) + R"CSS(;
  width: 8px; height: 8px;
}
QSpinBox::down-arrow, QDoubleSpinBox::down-arrow {
  image: url()CSS" + QString(ARROW_DOWN_LIGHT) + R"CSS(;
  width: 8px; height: 8px;
}

/* ---------- Buttons ---------- */
QPushButton {
  background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                              stop:0 #f4f4f4, stop:1 #eaeaea);
  border: 1px solid #d0d0d0;
  border-radius: 10px;
  padding: 6px 12px;
}
QPushButton:hover { background: #efefef; }
QPushButton:pressed { background: #e6e6e6; }

/* ---------- Menu ---------- */
QMenuBar {
  background: #f3f3f3;
  border-bottom: 1px solid #e3e3e3;
}
QMenu { background: #ffffff; border: 1px solid #e0e0e0; }
QMenu::item:selected { background: #e9f0ff; }

/* ---------- Table ---------- */
QHeaderView::section {
  background: #f0f0f0;
  border: 1px solid #e1e1e1;
  padding: 4px;
  border-radius: 6px;
}

/* ---------- Scrollbars ---------- */
QScrollBar:vertical {
  background: transparent; width: 12px; margin: 2px;
}
QScrollBar::handle:vertical {
  background: #d8d8d8; border-radius: 6px; min-height: 24px;
}
QScrollBar::handle:vertical:hover { background: #cfcfcf; }

QScrollBar:horizontal {
  background: transparent; height: 12px; margin: 2px;
}
QScrollBar::handle:horizontal {
  background: #d8d8d8; border-radius: 6px; min-width: 24px;
}
QScrollBar::handle:horizontal:hover { background: #cfcfcf; }

/* ---------- Gantt extras ---------- */
#GanttView {
  background: #ffffff;
  border: 1px solid #e7e7e7;
  border-radius: 10px;
}
)CSS");

/* ---------------- DARK THEME ---------------- */
inline QString THEME_DARK = QString(R"CSS(
/* ---------- Base ---------- */
QWidget {
  background-color: #1e1f22;
  color: #ececec;
  font-family: "Segoe UI", "Inter", "Noto Sans", sans-serif;
  font-size: 10.5pt;
}

/* ---------- Containers ---------- */
QGroupBox {
  border: 1px solid #2b2d31;
  border-radius: 10px;
  margin-top: 8px;
}
QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 4px; }

/* ---------- Inputs ---------- */
QLineEdit, QTextEdit, QPlainTextEdit, QComboBox, QSpinBox, QDoubleSpinBox, QTableWidget, QTableView {
  background: #2b2d31;
  border: 1px solid #3a3d43;
  border-radius: 8px;
  selection-background-color: #4c8dff;
  selection-color: #ffffff;
  color: #ececec;
}
QLineEdit:focus, QTextEdit:focus, QPlainTextEdit:focus, QComboBox:focus, QSpinBox:focus, QDoubleSpinBox:focus, QTableWidget:focus, QTableView:focus {
  border: 1px solid #5a98ff;
}

/* SpinBox buttons */
QSpinBox::up-button, QDoubleSpinBox::up-button {
  subcontrol-origin: border;
  subcontrol-position: top right;
  width: 16px;
  border-left: 1px solid #474b52;
  background: transparent;
}
QSpinBox::down-button, QDoubleSpinBox::down-button {
  subcontrol-origin: border;
  subcontrol-position: bottom right;
  width: 16px;
  border-left: 1px solid #474b52;
  background: transparent;
}
QSpinBox::up-arrow, QDoubleSpinBox::up-arrow {
  image: url()CSS" + QString(ARROW_UP_DARK) + R"CSS(;
  width: 8px; height: 8px;
}
QSpinBox::down-arrow, QDoubleSpinBox::down-arrow {
  image: url()CSS" + QString(ARROW_DOWN_DARK) + R"CSS(;
  width: 8px; height: 8px;
}

/* ---------- Buttons ---------- */
QPushButton {
  background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                              stop:0 #3a3d43, stop:1 #33363b);
  border: 1px solid #474b52;
  border-radius: 10px;
  padding: 6px 12px;
  color: #f3f3f3;
}
QPushButton:hover { background: #40444a; }
QPushButton:pressed { background: #36393f; }

/* ---------- Menu ---------- */
QMenuBar {
  background: #2a2c30;
  border-bottom: 1px solid #34373d;
}
QMenu { background: #2b2d31; border: 1px solid #3a3d43; }
QMenu::item:selected { background: #374050; }

/* ---------- Table ---------- */
QHeaderView::section {
  background: #2a2c30;
  border: 1px solid #3a3d43;
  padding: 4px;
  border-radius: 6px;
  color: #dcdcdc;
}

/* ---------- Scrollbars ---------- */
QScrollBar:vertical {
  background: transparent; width: 12px; margin: 2px;
}
QScrollBar::handle:vertical {
  background: #3b3e45; border-radius: 6px; min-height: 24px;
}
QScrollBar::handle:vertical:hover { background: #454952; }

QScrollBar:horizontal {
  background: transparent; height: 12px; margin: 2px;
}
QScrollBar::handle:horizontal {
  background: #3b3e45; border-radius: 6px; min-width: 24px;
}
QScrollBar::handle:horizontal:hover { background: #454952; }

/* ---------- Gantt extras ---------- */
#GanttView {
  background: #23252a;
  border: 1px solid #34373d;
  border-radius: 10px;
}
)CSS");

#endif // THEMES_HPP
