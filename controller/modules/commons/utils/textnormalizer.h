#ifndef UTILS_TEXTNORMALIZER_H
#define UTILS_TEXTNORMALIZER_H

#include <QObject>


namespace Utils {

class TextNormalizer : public QObject
{
    Q_OBJECT

public:
    explicit TextNormalizer(QObject *parent = 0);

public:
    static QString normalize(const QString &text);

private:
    static QString toLower(const QString &text);
    static QString toUpper(const QString &character);
    static QChar decomposition(const QChar &character);
    static void decomposition(QString &text);
};

} // namespace Utils

#endif // UTILS_TEXTNORMALIZER_H
