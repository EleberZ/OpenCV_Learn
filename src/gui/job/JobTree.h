#ifndef JOB_TREE_H
#define JOB_TREE_H

#include "JobEditViewImp.h"
#include <QMenu>
#include <QAction>
#include <QTreeWidget>
#include <QLineEdit>
#include <QPoint>
#include <QWidget>

class JobTree: public JobEditViewImp
{
	Q_OBJECT
public:
	JobTree(QWidget *parent = nullptr);

    // 通过 JobEditViewImp 继承
    void initWidget()override;
    void updateWidget()override;
    QTreeWidgetItem* addBlockToTreeWdt();
    QTreeWidgetItem *copyBlockToTreeWdt(QTreeWidgetItem *item);
    QTreeWidgetItem* copyBlockToTreeWdt(QTreeWidgetItem *item, QString text);
    void deleteBlockFromTreeWdt(QTreeWidgetItem *item);
signals:
    void sglBlockDoubleClicked(QTreeWidgetItem *item);
public slots:
    void slotNotifyJobEditView();
private slots:
    void slotAddBlockToTreeWdt(bool trigger);
    void slotCopyBlockToTreeWdt(bool trigger);
    void slotDeleteBlockFromTreeWdt(bool trigger);
    void slotGetCurrentItem(const QPoint &pos);
    void slotBlockDoubleClicked(QTreeWidgetItem *item, int column);
private:
	QTreeWidget *m_treeWdt;
    QTreeWidgetItem *m_currentItem;
    QMenu *m_menu_block;

    QAction *m_addBlockAct;
    QAction *m_copyBlockAct;
    QAction *m_deleteBlockAct;
    QLineEdit *m_edit1;
    int m_blockCount;
    
};


#endif // JOB_TREE_H
