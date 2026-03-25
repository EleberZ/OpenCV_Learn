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
    //virtual void attach(std::shared_ptr<JobEditViewImp> view, QString view_name) = 0;
    //virtual std::shared_ptr<JobEditViewImp> detach(QString view_name) = 0;
    //virtual void notify(std::shared_ptr<JobEditViewImp> view) = 0;
    //virtual void notify(QString view_name) = 0;
    //virtual void notify() = 0;
protected:
    std::map<QString, std::shared_ptr<JobEditViewImp>> m_views;
};
#endif // JOB_EDIT_MODELIMP_H
