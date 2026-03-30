#include "JobTree.h"
#include <QHBoxLayout>

JobTree::JobTree(QWidget* parent)
    :JobEditViewImp(parent)
{
    initWidget();


}
void JobTree::initWidget()
{
    m_treeWdt = new QTreeWidget(this);
    QHBoxLayout *main_hlyt = new QHBoxLayout(this);
    main_hlyt->addWidget(m_treeWdt);

    //QTreeWidgetItem *job_main_item =  new QTreeWidgetItem(m_treeWdt);
    //job_main_item->setText(0, "Job");
}
void JobTree::updateWidget()
{
}

QTreeWidgetItem* JobTree::addBlockToTreeWdt()
{
    QTreeWidgetItem *item = new QTreeWidgetItem(m_treeWdt);
    m_treeWdt->addTopLevelItem(item);
    int top_item_count = m_treeWdt->topLevelItemCount();
    item->setText(top_item_count, "Block"+QString::number(top_item_count));

    return item;
}

QTreeWidgetItem* JobTree::copyBlockToTreeWdt(QTreeWidgetItem *item, QString text)
{
    if (!item)
    {
        return nullptr;
    }
    QTreeWidgetItem *itemCopy = item->clone();
    int index = m_treeWdt->indexOfTopLevelItem(item)+1;
    itemCopy->setText(index, "Block" + QString::number(index));
    m_treeWdt->addTopLevelItem(itemCopy);

    return itemCopy;
}

void JobTree::deleteBlockFromTreeWdt(QTreeWidgetItem *item)
{
    if (!item)
    {
        return;
    }
    //m_treeWdt->removeItemWidget(item, 0);
    //m_treeWdt->takeTopLevelItem(m_treeWdt->indexOfTopLevelItem(item));
    delete item;
}

void JobTree::slotCopyBlockToTreeWdt(QTreeWidgetItem *item, QString text)
{
    copyBlockToTreeWdt(item, text);
}

void JobTree::slotDeleteBlockFromTreeWdt(QTreeWidgetItem *item)
{
    deleteBlockFromTreeWdt(item);
}

void JobTree::slotNotifyJobEditView()
{
}
