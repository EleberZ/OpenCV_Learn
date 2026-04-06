#include "JobConfig.h"

JobConfig::JobConfig(QWidget* parent)
    : JobEditViewImp(parent), m_job_block_name("Job Block Name:")
{
    setWindowTitle(m_job_block_name);
    initWidget();
    
}

void JobConfig::initWidget()
{
    
}

void JobConfig::updateWidget()
{
}

void JobConfig::slotJobBlockDoubleClicked(QTreeWidgetItem *item)
{
    QString name = item->text(0);
    setWindowTitle(name);


}

void JobConfig::slotNotifyJobEditView()
{
}

