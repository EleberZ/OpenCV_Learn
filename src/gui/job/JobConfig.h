#ifndef JOB_CONFIG_H
#define JOB_CONFIG_H

#include "JobEditViewImp.h"

#include<QTreeWidgetItem>
#include<QWidget>
#include<QComboBox>

class JobConfig : public JobEditViewImp
{
    Q_OBJECT
public:
    explicit JobConfig(QWidget *parent = nullptr);
    // 通过 JobEditViewImp 继承
    void initWidget()override;
    void updateWidget()override;
public slots:
    void slotNotifyJobEditView()override;
    void slotJobBlockDoubleClicked(QTreeWidgetItem *item);
private:
    QString m_job_block_name;
    QComboBox *m_cbox_job_mode;
};

#endif
