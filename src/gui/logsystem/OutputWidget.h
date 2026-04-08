#ifndef OUTPUT_WIDGET_H
#define OUTPUT_WIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QDateTime>

class OutputWidget : public QWidget
{
    Q_OBJECT
public:
    OutputWidget(QWidget *parent = nullptr);
    void initWidget();
    void appendText(const QString& text);
private:
    QTextEdit *m_output_edit;
    QDateTime m_datetime;
    QDate m_date;
};

#endif // OUTPUT_WIDGET_H
