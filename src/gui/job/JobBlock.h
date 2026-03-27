#ifndef JOB_BLOCK_H
#define JOB_BLOCK_H

#include <QWidget>
#include "JobEditViewImp.h"

class JobBlock : public JobEditViewImp
{
	Q_OBJECT
public:
	JobBlock(QWidget *parent = nullptr);
    void initWidget();
    void updateWidget();
public slots:
    void slotNotifyJobEditView();
};

#endif // JOB_BLOCK_H
