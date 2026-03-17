#include "ZDockTabContainer.h"
#include <QVBoxLayout>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDropEvent>

ZDockTabContainer::ZDockTabContainer(int layout, QWidget* parent)
    :QWidget(parent), m_tabbar(nullptr), m_stackedWidget(nullptr)
{
    setAcceptDrops(true);    //dock拖拽接收

    m_tabbar = new QTabBar(this);
    m_tabbar->setExpanding(false);
    m_tabbar->setMovable(true);
    m_tabbar->installEventFilter(this);
    m_tabbar->setStyleSheet(
        "QTabBar::tab{"
            "background-color:#f0f0f0;"
            "color:#333;"
            "padding: 6px 12px;"
            "margin:1px;"
            "border-radius:4px 4px 4px 4px;"
            "width:auto"
            "white-space:nowrap;"
        "}"
    );

    m_stackedWidget = new QStackedWidget(this);
    switch (layout)
    {
    case 0: 
    {
        QGridLayout* tab_vlyt = new QGridLayout(this);
        m_tabbar->setShape(QTabBar::RoundedSouth);
        tab_vlyt->setMargin(0);
        tab_vlyt->setSpacing(0);
        tab_vlyt->addWidget(m_stackedWidget, 0,0,1,8);
        tab_vlyt->addWidget(m_tabbar, 1, 0, 1, 8);
    }
    break;
    case 1:
    {
        QGridLayout* tab_vlyt = new QGridLayout(this);
        m_tabbar->setShape(QTabBar::RoundedWest);
        tab_vlyt->setMargin(0);
        tab_vlyt->setSpacing(0);
        tab_vlyt->addWidget(m_tabbar, 0,0,1,1);
        tab_vlyt->addWidget(m_stackedWidget, 0,1,8,1);
    }
    break;
    case 2:
    {
        QGridLayout* tab_vlyt = new QGridLayout(this);
        m_tabbar->setShape(QTabBar::RoundedEast);
        tab_vlyt->setMargin(0);
        tab_vlyt->setSpacing(0);
        tab_vlyt->addWidget(m_stackedWidget,0,0,8,1);
        tab_vlyt->addWidget(m_tabbar,0,1,1,1);
    }
    break;
    default:
        break;
    }
    m_tabbar->setVisible(true);
    connect(m_tabbar, &QTabBar::currentChanged, this, &ZDockTabContainer::slotTabChange);
}

ZDockTabContainer::~ZDockTabContainer()
{
}

void ZDockTabContainer::addDockTab(const QString& text, QDockWidget* widget) 
{
    if (!widget || containsDock(dock)
    {

    }
    int tabindex = m_tabbar->addTab(text);
        m_stackedWidget->addWidget(widget);
        widget->setStyleSheet(
        "QWidget{"
            "background-color:#f0f0f0;"
        "}"
    );
    m_tabbar->setCurrentIndex(tabindex);


}

void ZDockTabContainer::removeDockTab(const QString& text, QWidget* widget)
{
    QStackedWidget* stack_wdt = qobject_cast<QStackedWidget*>(widget->parent());
    int index = stack_wdt->indexOf(widget);
    m_stackedWidget->removeWidget(widget);
    m_tabbar->removeTab(index);
}

bool ZDockTabContainer::eventFilter(QObject* obj, QEvent* event)
{
    QDockWidget* dock = qobject_cast<QDockWidget*>(obj);
    if (!dock)
    {
        return QWidget::eventFilter(obj, event);
    }

    switch (event->type())
    {
    case QEvent::DragLeave:
    {
        
    }
    break;
    case QEvent::ParentChange:
    {
        if (dock->parent() != this 
            && dock->parent() != m_stackedWidget)
        {
            removeDockTab(dock->windowTitle(), dock);
        }
    }
    case QEvent::Close:
    {
        removeDockTab(dock->windowTitle(), dock);
    }
    default:
        break;
    }
    return QWidget::eventFilter(obj, event);
}

void ZDockTabContainer::dragLeaveEvent(QDragLeaveEvent* event)
{
}

void ZDockTabContainer::dragEnterEvent(QDragEnterEvent* event)
{
    const QMimeData* mimeData = event->mimeData();
    if (mimeData->hasFormat("application/x-dockwidget"))
    {
        //QDockWidget *dock = qobject_cast<QDockWidget*>();
        //允许放下
        event->acceptProposedAction();
        update();
    }
    else
    {
        event->ignore();
    }
}

void ZDockTabContainer::dragMoveEvent(QDragMoveEvent* event)
{
}

void ZDockTabContainer::dropEvent(QDropEvent* event)
{
    QDockWidget * dock = qobject_cast<QDockWidget*>(event->source());
    if (dock)
    {
        addDockTab(dock->windowTitle(), dock);
        event->acceptProposedAction();
    }
    else
    {
        event->ignore();
    }
}

void ZDockTabContainer::paintEvent(QPaintEvent* event)
{
}

void ZDockTabContainer::slotDockTopLevelChange(bool isFloating)
{
}

void ZDockTabContainer::slotDockFloatingChange(bool isFloating)
{
}


void ZDockTabContainer::slotTabChange(int index)
{
    m_stackedWidget->setCurrentIndex(index);
}
