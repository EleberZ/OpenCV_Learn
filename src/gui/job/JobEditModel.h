#ifndef JOB_EDIT_MODEL_H
#define JOB_EDIT_MODEL_H

#include "JobEditModelImp.h"
#include <QFile>
#include <QDomDocument>
#include <QTextStream>

struct BlockData
{
    ROIData roi_data;
    QString m_temp_picture_path;
    QString m_mask_picture_path;
    double xpos;
    double ypos;
    BlockData(): roi_data(), xpos(0), ypos(0){};
    BlockData(const BlockData &other);
    BlockData(BlockData &&other);
    BlockData& operator=(const BlockData &other);

    void setXpos(double xpos);
    double getXpos();
    void setYpos(double ypos);
    double getYpos();
    void setROIData(int width, int height, int stride, int threshold,
        int overlapThreshold, int max_match_count);
    ROIData getROIData();
    void setMaskPicturePath(QString mask_picture_path);
    QString getMaskPicturePath();
    void setTempPicturePath(QString temp_picture_path);
    QString getTempPicturePath();
};

enum ShapeEnum
{
    Circle,
    Rectangle,
};
struct ROIData
{
    double width;
    double height;
    int stride;
    int threshold;
    int overlapThreshold;
    int max_match_count;
    
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

    void addEmptyBlock(int index);
    void setROIData(double width, double height);
    BlockData getBlockData();
    ROIData getROIData();
signals:
    void sglNotifyJobEditView();
public slots:
    void slotNewJob(QString filepath);
    void slotSaveJob();
    void slotLoadJob(QString filepath);
private:
    std::unique_ptr<QFile> openFileIfExists(QString filepath);
    void addBlock(int index, QString mask_picture_path, 
        QString output_picture_path);
private:
    QString m_filepath; //被加载之后将路径保存在这个位置
    std::unique_ptr<QFile> m_job_file;
    QTextStream m_job_stream;
    QDomDocument m_job_xml;
    std::vector<BlockData> m_blocks_data;
};

#endif // JOB_EDIT_MODEL_H
