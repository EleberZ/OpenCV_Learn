#ifndef JOB_TREE_H
#define JOB_TREE_H

#include <QTreeWidget>
#include <QWidget>
#include "JobEditViewImp.h"

class JobTree: public JobEditViewImp
{
	Q_OBJECT
public:
	JobTree(QWidget *parent = nullptr);
    void initWidget();
    void updateWidget();
public slots:
    void slotNotifyJobEditView();
private:
	QTreeWidget *treeWidget;
};


#endif // JOB_TREE_H
