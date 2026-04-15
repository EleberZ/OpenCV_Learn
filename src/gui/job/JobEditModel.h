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
#include <map>
#include <qxmlstream.h>

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
    int m_match_method;
    cv::TemplateMatchModes m_template_match_type;
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

    void setTemplateMatchType(cv::TemplateMatchModes methor);
    cv::TemplateMatchModes getTemplateMatchType();

    void setMatchMethod(int match_method);
    int getMatchMethod();
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
    // Inherited via JobEditModelImp
    void setJobFilepath(QString filepath)override;
    QString getJobFilepath()override;
    bool NewJobFile(QString filepath)override;  
    void loadJobFile(QString filepath)override; 
    void saveJobFile()override;
    void setView(JobEditViewImp *view) override;

    void addEmptyBlock(int index);
    int copyBlock(int index);
    int deleteBlock(int index);
    BlockData getBlockData(int index);
    int getBlockCount();
    void setCurrentBlockIndex(int index);

signals:
    void sglloadJobFileSuccess();
    void sglNotifyJobEditView();
public slots:
    void slotNewJob(QString filepath);
    void slotSaveJob();
    void slotLoadJob(QString filepath);
    void slotBlockSave();
private:
    bool Xml_to_BlockMap();
    bool BlockMap_to_Xml();
    void createDTD();

    void editXmlFile();
    std::unique_ptr<QFile> openFileIfExists(QString filepath);
    void addBlock(int index, QString mask_picture_path, QString output_picture_path,
        double xpos, double ypos, ROIData roi_data);

    QDomNode createNodeIfNotExists(QDomNode& parent, QString name, QStringList attr_names, QStringList attr_value);
private:
    QString m_filepath; //被加载之后将路径保存在这个位置
    std::unique_ptr<QFile> m_job_file;
    QTextStream m_job_stream;
    QXmlStreamWriter m_job_xml_writer;
    QXmlStreamReader m_job_xml_reader;
    int m_current_block_index;
    std::vector<BlockData> m_blocks_data;
    std::map<int, BlockData> m_blocks_data1;
    QString m_dtd;
    QString m_xs;
    QString m_xsi;
};

#endif // JOB_EDIT_MODEL_H
