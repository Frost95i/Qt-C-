#ifndef SYMBOLS_H
#define SYMBOLS_H

#include <QString>
#include <tuple>

#include <optional>

class Symbols
{
public:
    Symbols() = default;

    std::optional<std::tuple<QString, int, int>> GetSpec(const QString& line) const;
    QString Special(const QString& line, const std::tuple<QString, int, int>&spec) const;
};

#endif // SYMBOLS_H
