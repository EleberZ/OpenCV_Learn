#ifndef OUTPUT_WIDGET_H
#define OUTPUT_WIDGET_H

#include <QWidget>
#include <QTextEdit>


class OutputWidget : public QWidget
{
    Q_OBJECT
public:
    OutputWidget(QWidget *parent = nullptr);
<<<<<<< HEAD
=======
    ~OutputWidget();
>>>>>>> cede7bf335a31cce20ae890e04d723e12abc47e0
    QTextEdit *textEdit;
    void appendText(const QString& text);

};

#endif // OUTPUT_WIDGET_H