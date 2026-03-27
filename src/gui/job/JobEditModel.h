#ifndef JOB_EDIT_MODEL_H
#define JOB_EDIT_MODEL_H

#include "JobEditModelImp.h"
#include <QFile>
#include <QDomDocument>
#include <QTextStream>

struct BlockData
{
private:
    ROIData *m_roi_data;
    QString m_temp_picture_path;
    QString m_mask_picture_path;
    double m_xpos;
    double m_ypos;
public:
    BlockData(): m_roi_data(nullptr), m_xpos(0), m_ypos(0){};
    BlockData(const BlockData &other)noexcept;
    BlockData(BlockData &&other)noexcept;
    BlockData& operator=(const BlockData &other)noexcept;
    BlockData& operator=(BlockData &&other)noexcept;
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
    double pix_x;
    double pix_y;
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
    BlockData getBlockData(int index);

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
