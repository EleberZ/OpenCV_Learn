#ifndef JOB_CONTROLLER_H
#define JOB_ CONTROLLER_H

#include "JobEditModelImp.h"
#include <QMainWindow>

class JobController 
{
public:
    JobController();
    void initConnect();
public slots:
    void slotLoadJob(QString jobName);
    void slotNewJob(QString jobName);
    void slotSaveJob();

    void setViews(std::shared_ptr<QWidget> view);
    void setView(QWidget* view);
    void setModels(std::shared_ptr<JobEditModelImp> model);
    void setModel(std::shared_ptr<JobEditModelImp> model);
private:
    void NewJob(QString name);
    void LoadJob(QString jobName);
    void SaveJob();
private:
    std::vector<std::shared_ptr<JobEditModelImp>>  m_models;
    std::vector<std::shared_ptr<QWidget>> m_views;
    std::shared_ptr<JobEditModelImp> m_model;
    QWidget* m_view;
};

#endif // JOB_CONTROLLER_H
