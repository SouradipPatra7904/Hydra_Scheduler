#ifndef GLOBALTHEMES_HPP
#define GLOBALTHEMES_HPP

#include <QString>

class GlobalThemes {
public:
    enum class ThemeMode { Fusion, DarkFusion };
    static QString getTheme(ThemeMode mode);
};

#endif // GLOBALTHEMES_HPP
