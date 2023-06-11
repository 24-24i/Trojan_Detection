#include "highlighter.h"

KeywordHighlighter::KeywordHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::blue);   //字体颜色
    keywordFormat.setBackground(Qt::white);  //背景颜色
    keywordFormat.setFontWeight(QFont::Bold); //字体加粗

    QStringList keywordPatterns;
    keywordPatterns << "\\bLUT*" <<  "\\bMUXF*"<< "\\bFDRE\\b"
                    << "\\bIBUF\\b" << "\\bOBUF\\b"; //关键词列表

    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }
}

void KeywordHighlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegularExpression expression(rule.pattern);
        QRegularExpressionMatch match = expression.match(text);
        while (match.hasMatch()) {
            int index = match.capturedStart();
            int length = match.capturedLength();
            setFormat(index, length, rule.format);
            match = expression.match(text, index + length);
        }
    }
}
