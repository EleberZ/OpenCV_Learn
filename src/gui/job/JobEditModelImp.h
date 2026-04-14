#ifndef JOB_EDIT_MODELIMP_H
#define JOB_EDIT_MODELIMP_H

#include <QObject>
#include "JobEditViewImp.h"

//被观察者
class JobEditModelImp : public QObject
{
    Q_OBJECT
public:
    explicit JobEditModelImp(QObject *parent = nullptr);
    virtual void setJobFilepath(QString filepath)= 0 ;
    virtual QString getJobFilepath() = 0;
    virtual bool NewJobFile(QString filepath) = 0;  
    virtual void loadJobFile(QString filepath) = 0; 
    virtual void saveJobFile() = 0;
    virtual void setView(JobEditViewImp *view) = 0;
protected:
    JobEditViewImp *m_view;
};
#endif // JOB_EDIT_MODELIMP_H
