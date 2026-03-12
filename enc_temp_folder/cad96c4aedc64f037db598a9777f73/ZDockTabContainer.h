#ifndef ZDOCKTABCONTAINER_H
#define ZDOCKTABCONTAINER_H

#include <QDockWidget>
#include <QTabBar>
#include <QStackedWidget>

class ZDockTabContainer:public QWidget
{
	Q_OBJECT
public:
	explicit ZDockTabContainer(int layout, QWidget *parent= nullptr);
	~ZDockTabContainer();
	void addDockTab(const QString &text, QWidget *widget);
	void removeDockTab(const QString &text, QWidget *widget);


protected:
	bool eventFilter(QObject* obj, QEvent* event) override;
	void dragLeaveEvent(QDragLeaveEvent *event) override;
	void dragEnterEvent(QDragEnterEvent *event) override;
	void dropEvent(QDropEvent *event) override;
	//void eventFilter(QObject *obj, QEvent *event) override;

private slots:
	void slotTabChange(int index);

private:
	QTabBar* m_tabbar;
	QStackedWidget* m_stackedWidget;


};


#endif // DOCKWIDGETCONTAINER_H