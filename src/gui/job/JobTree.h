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

    // 通过 JobEditViewImp 继承
    void initWidget()override;
    void updateWidget()override;
public slots:
    void slotNotifyJobEditView();
private:
	QTreeWidget *treeWidget;
};


#endif // JOB_TREE_H
