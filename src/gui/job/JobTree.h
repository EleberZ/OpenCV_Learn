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
    QTreeWidgetItem* addBlockToTreeWdt();
    QTreeWidgetItem* copyBlockToTreeWdt(QTreeWidgetItem *item, QString text);
    void deleteBlockFromTreeWdt(QTreeWidgetItem *item);
public slots:
    void slotNotifyJobEditView();
private slots:
    void slotCopyBlockToTreeWdt(QTreeWidgetItem *item, QString text);
    void slotDeleteBlockFromTreeWdt(QTreeWidgetItem *item);
private:
	QTreeWidget *m_treeWdt;
};


#endif // JOB_TREE_H
