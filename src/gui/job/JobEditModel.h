#ifndef JOB_EDIT_MODEL_H
#define JOB_EDIT_MODEL_H

#include "JobEditModelImp.h"

class JobEditModel : public JobEditModelImp
{
    Q_OBJECT
public:

    explicit JobEditModel(QObject *parent = nullptr);
    void setJobFilepath(QString filepath);
    QString getJobFilepath();
    void saveJobFile();
    void loadJobFile();


    //void attach(std::shared_ptr<JobEditViewImp> view, QString view_name) override;
    //std::shared_ptr<JobEditViewImp> detach(QString view_name) override;
    //void notify(std::shared_ptr<JobEditViewImp> view)override;
    //void notify(QString view_name) override;
    //void notify() override;


public slots:
    void slotNewJob();
    void slotSaveJob();
private:

};

#endif // JOB_EDIT_MODEL_H
