#ifndef TEXTHIGHLIGHTER_H
#define TEXTHIGHLIGHTER_H

#include <QObject>

class TextHighlighter : public QObject
{
    Q_OBJECT
private:
    explicit TextHighlighter(QObject *parent = nullptr);
public:
    static TextHighlighter* getInstance();

    Q_INVOKABLE QString highlightText(QString text, QString highlighted);
    Q_INVOKABLE void setHighlightColor(QString color);
private:
    QString highlightBlock(QString text);
    QString mHighlightColor;
signals:

};

#endif // TEXTHIGHLIGHTER_H
