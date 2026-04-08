#include "OutputWidget.h"
#include <QHBoxLayout>

OutputWidget::OutputWidget(QWidget* parent)
    :QWidget(parent)
{
    initWidget();
}

void OutputWidget::initWidget()
{
    m_output_edit = new QTextEdit(this);
    m_output_edit->setReadOnly(true);

    QHBoxLayout* main_layout = new QHBoxLayout(this);
    main_layout->addWidget(m_output_edit);
    setLayout(main_layout);
}

void OutputWidget::appendText(const QString& text)
{
    QString str = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    m_output_edit->append(str+">>> " + text);
}
