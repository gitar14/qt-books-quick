#include "texthighlighter.h"
#include <QDebug>

TextHighlighter::TextHighlighter(QObject *parent)
    : QObject{parent}
{

}

TextHighlighter *TextHighlighter::getInstance()
{
    static TextHighlighter instance;
    return &instance;
}

QString TextHighlighter::highlightText(QString text, QString highlighted)
{
    const int highlightLength = highlighted.length();

    if (highlightLength == 0) return text;

    const int textLength = text.length();

    QStringList blockList;
    int lastIndex = 0;
    do {
        bool matched = false;
        int nextIndex = text.indexOf(highlighted, lastIndex, Qt::CaseInsensitive);
        if (nextIndex >= 0) {
            matched = true;
        } else {
            nextIndex = textLength;
        }

        blockList.append(text.sliced(lastIndex, nextIndex - lastIndex));
        if (matched)
            blockList.append(highlightBlock(text.sliced(nextIndex, highlightLength)));

        lastIndex = nextIndex + highlightLength;
    } while (lastIndex < textLength);

    return blockList.join("");
}

void TextHighlighter::setHighlightColor(QString color)
{
    mHighlightColor = color;
}

QString TextHighlighter::highlightBlock(QString text)
{
    return QStringLiteral("<font color=\"%1\">%2</font>").arg(mHighlightColor).arg(text.toHtmlEscaped());
}
