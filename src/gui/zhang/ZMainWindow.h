#ifndef ZMAINWINDOW_H
#define ZMAINWINDOW_H

#include <QMainWindow>

class ZMainWindow :public QMainWindow
{
    Q_OBJECT
public:
    explicit ZMainWindow(QMainWindow* parent =nullptr);
    void addDockWidget(Qt::DockWidgetArea area, QDockWidget *dockwidget);
    QTabBar* m_tabbar;
};

#endif //ZMAINWINDOW_H