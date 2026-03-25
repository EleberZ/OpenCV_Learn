#include "ZDockWidget.h"
#include <QHBoxLayout>
#include <QStyle>
#include <QMouseEvent>
#include <QEvent>

ZDockWidget::ZDockWidget(const QString &title, QWidget *parent)
    : QDockWidget(title, parent)
{
    QWidget *titlebar = new QWidget(this);
    titlebar->setObjectName("titleBar");
    QHBoxLayout *layout = new QHBoxLayout(titlebar);
    layout->setContentsMargins(5, 0, 5, 0);
    layout->setSpacing(5);

    m_lab_title = new QLabel(title, this);
    m_lab_title->setStyleSheet("font-weight:bold:padding: 5px;");

    m_btn_minimize = new QToolButton(this);
    //m_btn_minimize->setArrowType(Qt::DownArrow);
    m_btn_close->setIcon(style()->standardPixmap(QStyle::SP_TitleBarMinButton));
    m_btn_minimize->setStyleSheet(
        "QToolButton { border: none; border-radius: 3px; }"
        "QToolButton:hover { background-color: rgba(0,0,0,0.1); }"
    );

    m_btn_close = new QToolButton(this);
    m_btn_close->setIcon(style()->standardPixmap(QStyle::SP_TitleBarCloseButton));
    m_btn_close->setStyleSheet(
        "QToolButton { border: none; border-radius: 3px; }"
        "QToolButton:hover { background-color: rgba(0,0,0,0.1); }"
    );

    QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    layout->addWidget(m_lab_title);
    layout->addItem(spacer);
    layout->addWidget(m_btn_minimize);
    layout->addWidget(m_btn_close);
    titlebar->setLayout(layout);
    setTitleBarWidget(titlebar);

    titlebar->installEventFilter(this);
    m_lab_title->installEventFilter(this);

    connect(m_btn_minimize, &QToolButton::clicked, this, &ZDockWidget::slotToggleCollapse);

    setFeatures(DockWidgetClosable | DockWidgetMovable);

    setMinimumHeight(40);
}

void ZDockWidget::setWidget(QWidget *widget)
{
    QDockWidget::setWidget(widget);
    m_contentWdt = widget;
}

bool ZDockWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (obj==m_lab_title||obj==titleBarWidget())
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            slotToggleCollapse();
            return true;
        }
    }
}

void ZDockWidget::slotToggleCollapse()
{
    if (!m_contentWdt)
    {
        return;
    }
    m_bCollapse = !m_bCollapse;
    m_btn_minimize->setArrowType(m_bCollapse ? Qt::UpArrow : Qt::DownArrow);
    if (m_bCollapse)
    {
        m_lab_title->setStyleSheet(
            "color: gray; font-weight: bold; padding: 5px;"
        );
    }
    else
    {
        m_lab_title->setStyleSheet(
            "color: black; font-weight: bold; padding: 5px;"
        );
    }
}
