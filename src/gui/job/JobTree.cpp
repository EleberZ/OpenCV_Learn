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
    m_treeWdt = new QTreeWidget( this);
    m_treeWdt->setHeaderLabel("*. Job");
    //m_treeWdt->setHeaderHidden(true);
    m_treeWdt->setContextMenuPolicy(Qt::CustomContextMenu);
    //m_treeWdt->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_treeWdt->setWindowTitle("Job Tree");

    m_addBlockAct = new QAction("Add Block", m_treeWdt);
    m_copyBlockAct = new QAction("Copy Block", m_treeWdt);
    m_deleteBlockAct = new QAction("Delete Block", m_treeWdt);

    //QGroupBox *gbox = new QGroupBox(this);
    QVBoxLayout *main_hlyt = new QVBoxLayout(this);
    main_hlyt->addWidget(m_treeWdt);
    setLayout(main_hlyt);


    connect(m_treeWdt, &QTreeWidget::customContextMenuRequested, this, &JobTree::slotGetCurrentItem);
    connect(m_addBlockAct, &QAction::triggered, this, &JobTree::slotAddBlockToTreeWdt);
    connect(m_copyBlockAct, &QAction::triggered, this, &JobTree::slotCopyBlockToTreeWdt);
    connect(m_deleteBlockAct, &QAction::triggered, this, &JobTree::slotDeleteBlockFromTreeWdt);
    connect(m_treeWdt, &QTreeWidget::itemClicked, this, &JobTree::slotBlockDoubleClicked);
}
void JobTree::updateWidget()
{
}

int JobTree::addBlockToTreeWdt()
{
    int add_index = -1;
    QTreeWidgetItem *item = new QTreeWidgetItem(m_treeWdt);
    add_index = m_blockCount + 1;
    item->setText(0, "Block"+QString::number(add_index));

    m_treeWdt->addTopLevelItem(item);
    m_blockCount++;
    return add_index;
}

int JobTree::copyBlockToTreeWdt(QTreeWidgetItem *item)
{
    int copy_index = -1;
    QTreeWidgetItem *item1;
    if (!item)
    {
        return copy_index;
    }
    QTreeWidgetItem *itemCopy = item->clone();
    int index = m_treeWdt->indexOfTopLevelItem(item);
    copy_index = index + 1;
    m_treeWdt->insertTopLevelItem(copy_index, itemCopy);
    m_blockCount++;

    int count = m_treeWdt->topLevelItemCount();
    for (int i = copy_index; i < count; i++)
    {
        item1 = m_treeWdt->topLevelItem(i);
        item1->setText(0, "Block" + QString::number(i + 1));
    }
    return copy_index;
}

int JobTree::deleteBlockFromTreeWdt(QTreeWidgetItem *item)
{
    QTreeWidgetItem *item1;
    int delete_index = -1;
    if (!item)
    {
        return delete_index;
    }
    delete_index = m_treeWdt->indexOfTopLevelItem(item);
    m_treeWdt->takeTopLevelItem(delete_index);
    m_blockCount--;

    int count = m_treeWdt->topLevelItemCount();
    for (int i = delete_index; i < count; i++)
    {
        item1 = m_treeWdt->topLevelItem(i);
        item1->setText(0, "Block" + QString::number(i+1));
    }
    delete item;
    item = nullptr;
    return delete_index;
}

void JobTree::slotAddBlockToTreeWdt(bool trigger)
{
    int tmp = addBlockToTreeWdt();
    emit sglAddBlockToTreeWdt(tmp);
}

void JobTree::slotCopyBlockToTreeWdt(bool trigger)
{
    int tmp = copyBlockToTreeWdt(m_currentItem);
    emit sglCopyBlockToTreeWdt(tmp);
}

void JobTree::slotDeleteBlockFromTreeWdt(bool trigger) 
{
    int tmp = deleteBlockFromTreeWdt(m_currentItem);
    emit sglDeleteBlockFromTreeWdt(tmp);
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
