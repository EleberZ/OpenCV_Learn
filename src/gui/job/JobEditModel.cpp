#include "JobEditModel.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDomDocument>
// #include <QDebug>
#include <QfileInfo>

BlockData::BlockData():
    m_roi_data(nullptr),
    m_temp_picture_path(""),
    m_mask_picture_path(""),
    m_xpos(0),
    m_ypos(0)
{
}

BlockData::~BlockData()
{
    delete m_roi_data;
    m_roi_data = nullptr;
}

BlockData::BlockData(const BlockData &other)noexcept :
    m_temp_picture_path(other.m_temp_picture_path),
    m_mask_picture_path(other.m_mask_picture_path),
    m_xpos(other.m_xpos),
    m_ypos(other.m_ypos)
{
    if (other.m_roi_data)
    {
        m_roi_data = new ROIData(*other.m_roi_data);
    }
    else
    {
        m_roi_data = nullptr;
    }
}

BlockData::BlockData(BlockData &&other)noexcept
    :m_roi_data(other.m_roi_data),
    m_temp_picture_path(std::move(other.m_temp_picture_path)),
    m_mask_picture_path(std::move(other.m_mask_picture_path)),
    m_xpos(other.m_xpos),
    m_ypos(other.m_ypos)
{
    other.m_roi_data = nullptr;
}

BlockData &BlockData::operator=(const BlockData &other)noexcept
{
    if (this != &other)
    {
        delete m_roi_data;
        if (other.m_roi_data)
        {
            m_roi_data = new ROIData(*other.m_roi_data);
        }
        else
        {
            m_roi_data = nullptr;
        }
    }
    return *this;
}

BlockData &BlockData::operator=(BlockData &&other)noexcept
{
    if (this != &other)
    {
        delete m_roi_data;
        m_roi_data = other.m_roi_data;
        other.m_roi_data = nullptr;
    }
    return *this;
}

void BlockData::setXpos(double xpos)
{
    m_xpos = xpos;
}

double BlockData::getXpos()
{
    return m_xpos;
}

void BlockData::setYpos(double ypos)
{
    m_ypos = ypos;
}

double BlockData::getYpos()
{
    return m_ypos;
}

void BlockData::setROIData(const ROIData &roi_data)
{
    if (!m_roi_data)
    {
        return;
    }
    *m_roi_data = roi_data;
}

void BlockData::setROIData(int width, int height, int stride, int threshold, int overlapThreshold, int max_match_count)
{
    m_roi_data->width = width;
    m_roi_data->height = height;
    m_roi_data->stride = stride;
    m_roi_data->threshold = threshold;
    m_roi_data->overlapThreshold = overlapThreshold;
    m_roi_data->max_match_count = max_match_count;
}

ROIData *BlockData::getROIData()
{
    return m_roi_data;
}

void BlockData::setMaskPicturePath(QString mask_picture_path)
{
    m_mask_picture_path = mask_picture_path;
}

QString BlockData::getMaskPicturePath()
{
    return m_mask_picture_path;
}

void BlockData::setTempPicturePath(QString temp_picture_path)
{
    m_temp_picture_path = temp_picture_path;
}

QString BlockData::getTempPicturePath()
{
    return m_temp_picture_path;
}



JobEditModel::JobEditModel(QObject *parent)
{
    m_job_file = nullptr;
}

void JobEditModel::setJobFilepath(QString filepath)
{
    m_filepath = filepath;
}

QString JobEditModel::getJobFilepath()
{
    return m_filepath;
}

void JobEditModel::NewJobFile(QString filepath)
{
    m_filepath = filepath;
    QFileInfo fileInfo(filepath);
    m_job_xml.clear();
    QDomProcessingInstruction xmlDecl = m_job_xml.createProcessingInstruction(
        "xml", "version='1.0' encoding='UTF-8'"
    );
    QDomElement rootElement = m_job_xml.createElement(fileInfo.baseName());
    m_job_xml.appendChild(xmlDecl);
    m_job_xml.appendChild(rootElement);
}

void JobEditModel::loadJobFile(QString filepath)
{
    QFileInfo info(filepath);
    QFile file;
    if (!info.exists())
    {
        return;
    }
    if (!file.open(QIODevice::ReadWrite))
    {
        return;
    }
    if (!m_job_xml.setContent(&file))
    {
        file.close();
        return;
    }
}

void JobEditModel::saveJobFile()
{
    QFile file(m_filepath);
    if (!file.open(QIODevice::ReadWrite))
    {
        return;
    }
    QTextStream out(&file);
    m_job_xml.save(out, 4);
}

BlockData JobEditModel::getBlockData(int index)
{
    if (!m_blocks_data.empty()
        && m_blocks_data.size() > index)
    {
        return m_blocks_data[index];
    }
    else
    {
        return BlockData();
    }
}

void JobEditModel::slotNewJob(QString filepath)
{
    NewJobFile(filepath);
    loadJobFile(filepath);
}

void JobEditModel::slotLoadJob(QString filepath)
{
    loadJobFile(filepath);
}

void JobEditModel::slotSaveJob()
{
    saveJobFile();
}

std::unique_ptr<QFile> JobEditModel::openFileIfExists(QString filepath)
{
    QFileInfo info(filepath);
    if (!info.exists())
    {
        return nullptr;
    }
    auto file = std::make_unique<QFile>(filepath);
    if (file.get()->open(QIODevice::ReadWrite))
    {
        return file;
    }
}

void JobEditModel::addBlock(int index, QString mask_picture_path, QString output_picture_path,
    double xpos, double ypos, ROIData roi_data)
{
    if (index < 0)
    {
        return;
    }
    BlockData block;
    block.setMaskPicturePath(mask_picture_path);
    block.setTempPicturePath(output_picture_path);
    block.setXpos(xpos);
    block.setYpos(ypos);
    block.setROIData(roi_data);
    m_blocks_data.insert(m_blocks_data.begin() + index, block);
}

void JobEditModel::addEmptyBlock(int index)
{
    if (index < 0)
    {
        return;
    }
    m_blocks_data.insert(m_blocks_data.begin() + index, BlockData());
}

