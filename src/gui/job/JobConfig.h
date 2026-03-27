#ifndef JOB_CONFIG_H
#define JOB_CONFIG_H

#include<QWidget>
#include "JobEditViewImp.h"

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
private:

};

#endif
