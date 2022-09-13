#include "symbols.h"

#include <QHash>

namespace
{
QHash<QString, QString> tags
    {
          {"#@EUR@", u8"\u20AC"},
          {"#@DOL@", u8"\u0024"},
          {"#@C@",   u8"\u00A9"},
          {"#@RUB@", u8"\u20BD"},
          {"#@DEG@", u8"\u2070"},
          {"#@PRO@", u8"\u2030"},
    };
}

std::optional<std::tuple<QString, int, int>> Symbols::GetSpec(const QString& line) const
{
    QHash<QString, QString>::const_iterator i = tags.constBegin();
    while (i != tags.constEnd())
    {
        if(int index = line.indexOf(i.key()); index != -1)
        {
            return std::make_tuple(i.value(), index, i.key().length());
        }
        ++i;
    }
    return std::nullopt;
}

QString Symbols::Special(const QString& line, const std::tuple<QString, int, int>& spec) const
{
    QString formattedText {line};
    const auto& [lexeme, pos, length] = spec;

    formattedText.replace(pos, length, lexeme);
    return formattedText;
}
