#include "ZMainWindow.h"

ZMainWindow::ZMainWindow(QMainWindow *parent)
    : QMainWindow(parent)
{
}

void ZMainWindow::addDockWidget(Qt::DockWidgetArea area, QDockWidget* dockwidget)
{

    QMainWindow::addDockWidget(area, dockwidget);
}
