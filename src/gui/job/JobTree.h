#ifndef JOB_TREE_H
#define JOB_TREE_H

#include <QTreeWidget>
#include <QWidget>

class JobTree: public QWidget
{
	Q_OBJECT
public:
	JobTree(QWidget *parent = nullptr);
	void initWidget();
private:
	QTreeWidget *treeWidget;
};


#endif // JOB_TREE_H