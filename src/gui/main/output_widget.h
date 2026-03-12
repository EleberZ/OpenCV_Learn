#ifndef OUTPUT_WIDGET_H
#define OUTPUT_WIDGET_H

#include <QWidget>
#include <QTextEdit>


class OutputWidget : public QWidget
{
    Q_OBJECT
public:
    OutputWidget(QWidget *parent = nullptr);
    ~OutputWidget();
    QTextEdit *textEdit;
    void appendText(const QString& text);

};

#endif // OUTPUT_WIDGET_H