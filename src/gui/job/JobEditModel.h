#ifndef JOB_EDIT_MODEL_H
#define JOB_EDIT_MODEL_H

#include "JobEditModelImp.h"
#include <opencv2/imgproc.hpp>
#include <QDomDocument>
#include <QFile>
#include <QMetaObject>
#include <QMetaProperty>
#include <QObject>
#include <QTextStream>

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
struct BlockData
{
        
private:
    QString m_temp_picture_path;
    QString m_mask_picture_path;
    double m_xpos;
    double m_ypos;
    ROIData *m_roi_data;
    cv::TemplateMatchModes m_template_match_methor;
public:
    BlockData();
    ~BlockData();
    BlockData(const BlockData &other)noexcept;
    BlockData& operator=(const BlockData &other)noexcept;
    BlockData(BlockData &&other)noexcept;
    BlockData& operator=(BlockData &&other)noexcept;
    void setXpos(double xpos);
    double getXpos();
    void setYpos(double ypos);
    double getYpos();

    void setROIData(const ROIData &roi_data);
    void setROIData(int width, int height, int stride, int threshold,
        int overlapThreshold, int max_match_count);
    ROIData* getROIData();
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
    void sglloadJobFileSuccess();
    void sglNotifyJobEditView();
public slots:
    void slotNewJob(QString filepath);
    void slotSaveJob();
    void slotLoadJob(QString filepath);
    void slotBlockSave();
private:
    void editXmlFile();
    std::unique_ptr<QFile> openFileIfExists(QString filepath);
    void addBlock(int index, QString mask_picture_path, QString output_picture_path,
        double xpos, double ypos, ROIData roi_data);
private:
    QString m_filepath; //被加载之后将路径保存在这个位置
    std::unique_ptr<QFile> m_job_file;
    QTextStream m_job_stream;
    QDomDocument m_job_xml;
    std::vector<BlockData> m_blocks_data;
};

#endif // JOB_EDIT_MODEL_H
