#include "JobController.h"
#include "JobEditModel.h"

JobController::JobController()
{
}

void JobController::initConnect()
{
}

void JobController::NewJob(QString jobName)
{
    m_model->NewJobFile(jobName);
}

void JobController::LoadJob(QString jobName)
{
    m_model->loadJobFile(jobName);
}

void JobController::SaveJob()
{
    m_model->saveJobFile();
}

void JobController::slotLoadJob(QString jobName)
{
    LoadJob(jobName);
}


void JobController::slotNewJob(QString jobName)
{
    NewJob(jobName);
}

void JobController::slotSaveJob()
{
    SaveJob();
}

void JobController::setViews(std::shared_ptr<QWidget> view)
{
    if (view.get() == nullptr)
    {
        return;
    }
    m_views.push_back(view);
}

void JobController::setView(QWidget *view)
{
    m_view = view;
}

void JobController::setModels(std::shared_ptr<JobEditModelImp> model)
{
    if (model.get()==nullptr)
    {
        return;
    }
    m_models.push_back(model);
}

void JobController::setModel(std::shared_ptr<JobEditModelImp> model)
{
    if (model.get() == nullptr)
    {
        return;
    }
    m_model = model;
}
