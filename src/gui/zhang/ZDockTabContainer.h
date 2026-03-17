#ifndef ZDOCKTABCONTAINER_H
#define ZDOCKTABCONTAINER_H

#include <QDockWidget>
#include <QTabBar>
#include <QMap>
#include <QStackedWidget>

class ZDockTabContainer:public QWidget
{
	Q_OBJECT
public:
	explicit ZDockTabContainer(int layout, QWidget *parent= nullptr);
	~ZDockTabContainer();
	void addDockTab(const QString &text, QDockWidget * dock);
	void removeDockTab(const QString &text, QWidget *widget);
	void containDock(const QDockWidget& dock);

protected:
	bool eventFilter(QObject* obj, QEvent* event) override;
	void dragEnterEvent(QDragEnterEvent *event) override;
	void dragMoveEvent(QDragMoveEvent *event) override;
	void dragLeaveEvent(QDragLeaveEvent *event) override;
	void dropEvent(QDropEvent *event) override;
	void paintEvent(QPaintEvent *event) override;
	//void eventFilter(QObject *obj, QEvent *event) override;

private slots:
	void slotTabChange(int index);
	void slotDockTopLevelChange(bool isFloating);
	void slotDockFloatingChange(bool isFloating);

private:
	QTabBar* m_tabbar;
	QStackedWidget* m_stackedWidget;

	QString m_containerName;
	QDockWidget* m_draggingDock = nullptr;
	bool m_isDragOver = false; 
	//QMap<QDockWidget*, QMetaObject::Connection> m_dockConnections; 

	QMap<int, QDockWidget*> m_index_dockMap;
	QMap<QString, QDockWidget*> m_dockMap;
};


#endif // DOCKWIDGETCONTAINER_H