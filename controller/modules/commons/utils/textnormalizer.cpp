#include "textnormalizer.h"

namespace Utils {

TextNormalizer::TextNormalizer(QObject *parent)
    : QObject(parent)
{
}


QString TextNormalizer::toLower(const QString &text)
{
    return text.toLower();
}


QString TextNormalizer::toUpper(const QString &text)
{
    return text.toUpper();
}


QChar TextNormalizer::decomposition(const QChar &character)
{
    if (character.isNull())
        return QChar();

    QString compositionString = character.decomposition();
    if (compositionString.isEmpty())
        return character;

    QChar firstDecompositionChar = compositionString.at(0);
    compositionString = firstDecompositionChar.decomposition();
    if (compositionString.isEmpty())
        return firstDecompositionChar;

    return compositionString.at(0);
}


void TextNormalizer::decomposition(QString &text)
{
    if (text.isEmpty())
        return;

    for (int index = 0; index < text.size(); ++index) {
        text[index] = decomposition(text.at(index));
    }
}


QString TextNormalizer::normalize(const QString &text)
{
    QString normalizedText = text;
    decomposition(normalizedText);
    normalizedText = normalizedText.toLower();
    return normalizedText;
}

} // namespace Utils
