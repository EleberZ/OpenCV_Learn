#ifndef JOB_BLOCK_H
#define JOB_BLOCK_H

#include <QWidget>
#include "JobEditViewImp.h"

class JobBlock : public JobEditViewImp
{
	Q_OBJECT
public:
	JobBlock(QWidget *parent = nullptr);

    // 通过 JobEditViewImp 继承
    void updateWidget() override;
    void initWidget() override;

public slots:
    void slotNotifyJobEditView();
};

#endif // JOB_BLOCK_H
