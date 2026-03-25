#ifndef JOB_EDIT_MODEL_H
#define JOB_EDIT_MODEL_H

#include "JobEditModelImp.h"
#include <QFile>
#include <QDomDocument>
#include <QTextStream>

struct BlockData
{
    QString name;
    double xpos;
    double ypos;
};

enum ShapeEnum
{
    Circle,
    Mask
};
struct ROIData
{
    double width;
    double height;
};

struct ShapeData
{
    ShapeEnum shape;
    double radius;
    double width;
};


class JobEditModel : public JobEditModelImp
{
    Q_OBJECT
public:
    explicit JobEditModel(QObject *parent = nullptr);
    void setJobFilepath(QString filepath)override;
    QString getJobFilepath()override;
    void NewJobFile(QString filepath)override;  
    void loadJobFile(QString filepath)override; 
    void saveJobFile()override;

    void setBlockData(QString name, double xpos, double ypos);
    void setROIData(double width, double height);
    void setShapeData(ShapeEnum shape, double radius, double width);
    BlockData getBlockData();
    ROIData getROIData();
    ShapeData getShapeData();
signals:
    void sglNotifyJobEditView();
public slots:
    void slotNewJob(QString filepath);
    void slotSaveJob();
    void slotLoadJob(QString filepath);
private:
    std::unique_ptr<QFile> openFileIfExists(QString filepath);
    QString m_filepath; //被加载之后将路径保存在这个位置
    std::unique_ptr<QFile> m_job_file;
    QTextStream m_job_stream;
    QDomDocument m_job_xml;
};

#endif // JOB_EDIT_MODEL_H
