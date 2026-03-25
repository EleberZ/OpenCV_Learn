#include "JobEditModel.h"

JobEditModel::JobEditModel(QObject *parent)
{
}

void JobEditModel::setJobFilepath(QString filepath)
{
}

QString JobEditModel::getJobFilepath()
{
    return QString();
}

void JobEditModel::saveJobFile()
{
}

void JobEditModel::loadJobFile()
{
}

//void JobEditModel::attach(std::shared_ptr<JobEditViewImp> view, QString view_name)
//{
//    m_views.emplace(view_name, view);
//}
//
//std::shared_ptr<JobEditViewImp> JobEditModel::detach(QString view_name)
//{
//    auto iter = m_views.find(view_name);
//    if (iter == m_views.end())
//    {
//        return nullptr;
//    }
//    else
//    {
//        m_views.erase(iter);
//    }
//    return iter->second;
//}
//
//void JobEditModel::notify(std::shared_ptr<JobEditViewImp> view)
//{
//    view->updateWidget();
//}
//
//void JobEditModel::notify(QString view_name)
//{
//    auto iter = m_views.find(view_name);
//    iter->second->updateWidget();
//}
//
//
//void JobEditModel::notify()
//{
//    for (auto tmp : m_views)
//    {
//        tmp.second->updateWidget();
//    }
//}

void JobEditModel::slotNewJob()
{
}

void JobEditModel::slotSaveJob()
{
}
