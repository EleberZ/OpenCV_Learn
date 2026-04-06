#include "JobTree.h"
#include <QHBoxLayout>
#include <QGroupBox>
#include <QStringList>

JobTree::JobTree(QWidget* parent)
    :JobEditViewImp(parent), m_blockCount(0)
{
    setWindowTitle("Job Tree");
    initWidget();
}
void JobTree::initWidget()
{
    m_treeWdt = new QTreeWidget(this);
    m_treeWdt->setContextMenuPolicy(Qt::CustomContextMenu);
    //m_treeWdt->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_treeWdt->setWindowTitle("Job Tree");

    m_addBlockAct = new QAction("Add Block", m_treeWdt);
    m_copyBlockAct = new QAction("Copy Block", m_treeWdt);
    m_deleteBlockAct = new QAction("Delete Block", m_treeWdt);

    //QGroupBox *gbox = new QGroupBox(this);
    QVBoxLayout *main_hlyt = new QVBoxLayout(this);
    main_hlyt->addWidget(m_treeWdt);

    connect(m_treeWdt, &QTreeWidget::customContextMenuRequested, this, &JobTree::slotGetCurrentItem);
    connect(m_addBlockAct, &QAction::triggered, this, &JobTree::slotAddBlockToTreeWdt);
    connect(m_copyBlockAct, &QAction::triggered, this, &JobTree::slotCopyBlockToTreeWdt);
    connect(m_deleteBlockAct, &QAction::triggered, this, &JobTree::slotDeleteBlockFromTreeWdt);
    connect(m_treeWdt, &QTreeWidget::itemDoubleClicked, this, &JobTree::slotBlockDoubleClicked);
}
void JobTree::updateWidget()
{
}

QTreeWidgetItem* JobTree::addBlockToTreeWdt()
{
    //m_treeWdt->setColumnCount(1);
    QTreeWidgetItem *item = new QTreeWidgetItem(m_treeWdt);
    item->setText(0, "Block"+QString::number(m_blockCount+1));
    m_treeWdt->addTopLevelItem(item);
    m_blockCount++;
    return item;

}

QTreeWidgetItem* JobTree::copyBlockToTreeWdt(QTreeWidgetItem *item)
{
    if (!item)
    {
        return nullptr;
    }
    QTreeWidgetItem *itemCopy = item->clone();
    itemCopy->setText(0, "Block" + QString::number(m_blockCount+1));
    m_treeWdt->addTopLevelItem(itemCopy);
    m_blockCount++;

    return itemCopy;
}

void JobTree::deleteBlockFromTreeWdt(QTreeWidgetItem *item)
{
    QTreeWidgetItem *item1;
    if (!m_currentItem)
    {
        return;
    }
    int delete_index = m_treeWdt->indexOfTopLevelItem(m_currentItem);
    m_treeWdt->takeTopLevelItem(delete_index);
    m_blockCount--;
    int count = m_treeWdt->topLevelItemCount();
    for (int i = delete_index; i < count; i++)
    {
        item1 = m_treeWdt->topLevelItem(i);
        item1->setText(0, "Block" + QString::number(i+1));
    }
    //m_treeWdt->removeItemWidget(item, 0);
    delete m_currentItem;
}

void JobTree::slotAddBlockToTreeWdt(bool trigger)
{
    addBlockToTreeWdt();
}

void JobTree::slotCopyBlockToTreeWdt(bool trigger)
{
    //QTreeWidgetItem *item = qobject_cast<QTreeWidgetItem *>(QObject::sender()->parent());
    //QTreeWidgetItem *item = m_treeWdt->itemAt();
    copyBlockToTreeWdt(m_currentItem);
}

void JobTree::slotDeleteBlockFromTreeWdt(bool trigger) 
{
    //QTreeWidgetItem *item = qobject_cast<QTreeWidgetItem *>(QObject::sender()->parent());
    deleteBlockFromTreeWdt(m_currentItem);
}

void JobTree::slotGetCurrentItem(const QPoint &pos)
{
    QMenu menu(this);
    menu.addAction(m_addBlockAct);
    menu.addAction(m_copyBlockAct);
    menu.addAction(m_deleteBlockAct);

    m_currentItem = m_treeWdt->itemAt(pos);
    if (m_currentItem)
    {
        m_copyBlockAct->setEnabled(true);
        m_deleteBlockAct->setEnabled(true);
    }
    else
    {
        m_copyBlockAct->setEnabled(false);
        m_deleteBlockAct->setEnabled(false);
    }
    menu.exec(mapToGlobal(pos));
}

void JobTree::slotBlockDoubleClicked(QTreeWidgetItem *item, int column)
{
    if (!item)
    {
        return;
    }

    emit sglBlockDoubleClicked(item);
}

void JobTree::slotNotifyJobEditView()
{
}
