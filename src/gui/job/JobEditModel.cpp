#include "JobEditModel.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDomDocument>
// #include <QDebug>
#include <QfileInfo>
#include <QDebug>
#include <QStack>

BlockData::BlockData():
    m_roi_data(nullptr),
    m_temp_picture_path("./picture/"),
    m_mask_picture_path("./picture/mask/"),
    m_xpos(0),
    m_ypos(0),
    m_match_method(QString()),
    m_template_match_type(cv::TM_SQDIFF)
{
    m_roi_data = new ROIData();
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
    m_ypos(other.m_ypos),
    m_match_method(other.m_match_method),
    m_template_match_type(other.m_template_match_type)
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
    m_ypos(other.m_ypos),
    m_match_method(other.m_match_method),
    m_template_match_type(other.m_template_match_type)
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

void BlockData::setEnable(bool enable)
{
    m_enable = enable;
}

bool BlockData::getEnable()
{
    return m_enable;
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

void BlockData::setROIData(double pix_x, double piy_y, double width, double height,
    double stride, int threshold, double overlapThreshold, int max_match_count)
{
    m_roi_data->pix_x = pix_x;
    m_roi_data->pix_y = piy_y;
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

void BlockData::setTemplateMatchType(int methor)
{
    m_template_match_type = methor;
}

int BlockData::getTemplateMatchType()
{
    return m_template_match_type;
}

void BlockData::setMethod(QString match_method)
{
    m_match_method = match_method;
}

QString BlockData::getMatchMethod()
{
    return m_match_method;
}

JobEditModel::JobEditModel(QObject *parent)
{
    //m_blocks_data1 = new std::map<int, BlockData>();
    m_job_file = nullptr;
    m_dtd = R"(
    <!DOCTYPE Job[
        <!ELEMENT Job (BlockCount, Block*)>
        <!ATTLIST Job id ID #REQUIRED >
        <!ELEMENT BlockCount (#PCDATA)>
        <!ATTLIST BlockCount id ID #REQUIRED >
        <!ELEMENT Block (MatchMethod, MatchType, Position, MaskPath, TempPath, ROIData)>
        <!ATTLIST Block id ID #REQUIRED >
        <!ELEMENT MatchMethod (#PCDATA)>
        <!ATTLIST MatchMethod id ID #REQUIRED >
        <!ELEMENT MatchType (#PCDATA)>
        <!ATTLIST MatchType id ID #REQUIRED >
        <!ELEMENT Position EMPTY>
        <!ATTLIST Position id ID #REQUIRED x CDATA #REQUIRED y CDATA #REQUIRED >
        <!ELEMENT MaskPath (#PCDATA)>
        <!ATTLIST MaskPath id ID #REQUIRED >
        <!ELEMENT TempPath (#PCDATA)>
        <!ATTLIST TempPath id ID #REQUIRED >
        <!ELEMENT ROIData EMPTY>
        <!ATTLIST ROIData id ID #REQUIRED pix_x CDATA #REQUIRED pix_y CDATA #REQUIRED width CDATA #REQUIRED height
            CDATA #REQUIRED stride CDATA #REQUIRED threshold CDATA #REQUIRED overlapThreshold
            CDATA #REQUIRED max_match_count CDATA #REQUIRED >
    ]>)";
    m_xs = "http://www.w3.org/2001/XMLSchema";
    m_xsi = "http://www.w3.org/2001/XMLSchema-instance";

}

void JobEditModel::setJobFilepath(QString filepath)
{
    m_filepath = filepath;
}

QString JobEditModel::getJobFilepath()
{
    return m_filepath;
}

bool JobEditModel::NewJobFile(QString filepath)
{
    m_filepath = filepath;
    WriteTemplateMatchXml();
}

void JobEditModel::loadJobFile(QString filepath)
{
    //TODO:需要添加更新job_xml的功能
    ReadTemplateMatchXml();
    emit sglloadJobFileSuccess();
}

void JobEditModel::saveJobFile()
{
    WriteTemplateMatchXml();
}

void JobEditModel::setView(JobEditViewImp *view)
{
    m_view = view;
}

BlockData JobEditModel::getBlockData(int index)
{
    auto it = m_blocks_data1.find(index);
    if (!m_blocks_data1.empty()
        &&it != m_blocks_data1.end())
    {
        return it->second;
    }
    else
    {
        return BlockData();
    }
}

void JobEditModel::setBlockData(int index, BlockData block_data)
{
    m_blocks_data1[index] = block_data;
}

int JobEditModel::getBlockCount()
{
    return m_blocks_data1.size();
}

void JobEditModel::setCurrentBlockIndex(int index)
{
    m_current_block_index = index;
}

QString JobEditModel::getJobId()
{
    return m_job_id;
}

void JobEditModel::setJobId(QString job_id)
{
    m_job_id = job_id;
}

int JobEditModel::copyBlock(int index)
{
    BlockData tmp;
    auto it = m_blocks_data1.find(index);
    m_blocks_data1.emplace(index + 1, it->second);
}

int JobEditModel::deleteBlock(int index)
{
    int rtn = m_blocks_data1.erase(index);
    return rtn;
}

void JobEditModel::slotNewJob(QString filepath)
{
    m_filepath = filepath;
    NewJobFile(filepath);
    loadJobFile(filepath);
}

void JobEditModel::slotLoadJob(QString filepath)
{
    m_filepath = filepath;
    loadJobFile(filepath);
}

void JobEditModel::slotBlockSave()
{
    //TODO:Block 保存
}

void JobEditModel::slotSaveJob()
{
    saveJobFile();
}

bool JobEditModel::Xml_to_BlockMap()
{
    BlockData block;
    QDomElement block_elem;

    return false;
}

bool JobEditModel::BlockMap_to_Xml()
{
    return false;
}

bool JobEditModel::WriteTemplateMatchXml()
{
    int i = 1;
    QFileInfo fileInfo(m_filepath);
    QFile file(m_filepath);
    if (!file.open(QIODevice::ReadWrite))
    {
        return false;
    }
    m_job_xml_writer.setDevice(&file);
    m_job_xml_writer.setAutoFormatting(true);
    m_job_xml_writer.writeStartDocument("1.0", "UTF-8");
    m_job_xml_writer.writeDTD(m_dtd);
    {
        //<job>
        m_job_xml_writer.writeStartElement("Job");
        m_job_xml_writer.writeAttribute("id", fileInfo.baseName());
        m_job_xml_writer.writeAttribute("xmlns:xsi", m_xsi);
        m_job_xml_writer.writeAttribute("xmlns:xs", m_xs);
        {
            //<BlockCount>
            m_job_xml_writer.writeStartElement("BlockCount");
            m_job_xml_writer.writeAttribute("id", "blockCount");
            m_job_xml_writer.writeAttribute("type", "int");
            m_job_xml_writer.writeCharacters(QString::number(m_blocks_data1.size()));
            m_job_xml_writer.writeEndElement();
            //<Block>
            for (auto &block:m_blocks_data1)
            {
                QString block_id = "block"+QString::number(i);
                m_job_xml_writer.writeStartElement("Block");
                m_job_xml_writer.writeAttribute("id", block_id);
                {
                    //<MatchMethod>
                    m_job_xml_writer.writeStartElement("MatchMethod");
                    m_job_xml_writer.writeAttribute("id", "match_method"+ QString::number(i));
                    {
                        m_job_xml_writer.writeCharacters(block.second.getMatchMethod());
                    }
                    m_job_xml_writer.writeEndElement();
                    //<MatchType>
                    m_job_xml_writer.writeStartElement("MatchType");
                    m_job_xml_writer.writeAttribute("id", "match_type" + QString::number(i));
                    {
                        m_job_xml_writer.writeCharacters(QString::number(block.second.getTemplateMatchType()));
                    }
                    m_job_xml_writer.writeEndElement();
                    //<Position>
                    m_job_xml_writer.writeStartElement("Position");
                    m_job_xml_writer.writeAttribute("id", "position"+ QString::number(i));
                    m_job_xml_writer.writeAttribute("x", QString::number(block.second.getXpos(), 'f'));
                    m_job_xml_writer.writeAttribute("y", QString::number(block.second.getYpos(), 'f'));
                    m_job_xml_writer.writeEndElement();
                    //<MaskPath>
                    m_job_xml_writer.writeStartElement("MaskPath");
                    m_job_xml_writer.writeAttribute("id", "mask_path"+ QString::number(i));
                    {
                        m_job_xml_writer.writeCharacters(block.second.getMaskPicturePath());
                    }
                    m_job_xml_writer.writeEndElement();
                    //<TempPath>
                    m_job_xml_writer.writeStartElement("TempPath");
                    m_job_xml_writer.writeAttribute("id", "temp_path" + QString::number(i));
                    {
                        m_job_xml_writer.writeCharacters(block.second.getTempPicturePath());
                    }
                    m_job_xml_writer.writeEndElement();

                    //<ROIData>
                    ROIData roi_data = *block.second.getROIData();
                    m_job_xml_writer.writeStartElement("ROIData");
                    m_job_xml_writer.writeAttribute("id", "roi_data" + QString::number(i));
                    m_job_xml_writer.writeAttribute("pix_x", QString::number(roi_data.pix_x, 'f'));
                    m_job_xml_writer.writeAttribute("pix_y", QString::number(roi_data.pix_y, 'f'));
                    m_job_xml_writer.writeAttribute("width", QString::number(roi_data.width, 'f'));
                    m_job_xml_writer.writeAttribute("height", QString::number(roi_data.height, 'f'));
                    m_job_xml_writer.writeAttribute("stride", QString::number(roi_data.stride, 'f'));
                    m_job_xml_writer.writeAttribute("threshold", QString::number(roi_data.threshold));          //匹配分数阈值
                    m_job_xml_writer.writeAttribute("overlapThreshold", QString::number(roi_data.overlapThreshold, 'f'));       //重叠阈值
                    m_job_xml_writer.writeAttribute("max_match_count", QString::number(roi_data.max_match_count));       //最大匹配数量
                    m_job_xml_writer.writeEndElement();
                }
                m_job_xml_writer.writeEndElement();
                i++;
            }
        }
        m_job_xml_writer.writeEndElement();
    }
    m_job_xml_writer.writeEndDocument();

    file.close();
    return true;
}

void JobEditModel::ReadTemplateMatchXml()
{
    QStack<QStringRef> stack;
    int index=0;
    QFileInfo fileInfo(m_filepath);
    QFile file(m_filepath);
    if (!fileInfo.exists())
    {
        return;
    }
    if (!file.open(QIODevice::ReadWrite))
    {
        return;
    }
    m_job_xml_reader.setDevice(&file);

    while (!m_job_xml_reader.atEnd()
        && !m_job_xml_reader.hasError())
    {
        auto token =  m_job_xml_reader.readNext();

        if (m_job_xml_reader.isStartDocument())
        {
            continue;
        }
        if (m_job_xml_reader.isEndDocument())
        {
            break;
        }
        if (m_job_xml_reader.isStartElement())
        {
            if (m_job_xml_reader.name() == "Job")
            {
                m_job_id = m_job_xml_reader.attributes().value("id").toString();
            }
            else if (m_job_xml_reader.name() == "Block")
            {
                QString str = m_job_xml_reader.attributes().value("id").toString();
                index = str.remove("block").toUInt();
                m_blocks_data1[index] = BlockData();
            }
            else if (m_job_xml_reader.name() == "Position")
            {
                double xpos = m_job_xml_reader.attributes().value("x").toDouble();
                double ypos = m_job_xml_reader.attributes().value("y").toDouble();
                bool enable = m_job_xml_reader.attributes().value("enable").toShort();
                m_blocks_data1[index].setXpos(xpos);
                m_blocks_data1[index].setYpos(ypos);
            }
            else if (m_job_xml_reader.name() == "ROIData")
            {
                double pix_x = m_job_xml_reader.attributes().value("pix_x").toDouble();
                double pix_y = m_job_xml_reader.attributes().value("pix_y").toDouble();
                double width = m_job_xml_reader.attributes().value("width").toDouble();
                double height = m_job_xml_reader.attributes().value("height").toDouble();
                double stride = m_job_xml_reader.attributes().value("stride").toInt();
                int threshold = m_job_xml_reader.attributes().value("threshold").toInt();
                double overlapThreshold = m_job_xml_reader.attributes().value("overlapThreshold").toDouble();
                int max_match_count = m_job_xml_reader.attributes().value("max_match_count").toInt();

                m_blocks_data1[index].setROIData(pix_x, pix_y, width, height,
                    stride, threshold, overlapThreshold, max_match_count);
                m_job_xml_reader.skipCurrentElement(); // 跳过剩余子元素
            }
            stack.push(m_job_xml_reader.name());
        }
        if (m_job_xml_reader.isEndElement())
        {
            if (stack.top() == m_job_xml_reader.name())
            {
                stack.pop();
            }
        }
        if (m_job_xml_reader.isCharacters())
        {
            QStringRef txt = stack.top();
            if (txt == "BlockCount")
            {
                int block_count = m_job_xml_reader.text().toInt();
                m_block_count = block_count;
            }
            else if (txt == "MatchMethod")
            {
                QString match_method = m_job_xml_reader.text().toString();
                m_blocks_data1[index].setMethod(match_method);
            }
            else if (txt == "MatchType")
            {
                QString match_method = m_job_xml_reader.text().toString();
                m_blocks_data1[index].setMethod(match_method);
            }
            else if (txt == "MaskPath")
            {
                QString mask_path = m_job_xml_reader.text().toString();
                m_blocks_data1[index].setMaskPicturePath(mask_path);
            }
            else if (txt == "TempPath")
            {
                QString temp_path = m_job_xml_reader.text().toString();
                m_blocks_data1[index].setTempPicturePath(temp_path);
            }
        }
        if (m_job_xml_reader.isEntityReference())
        {

        }
    }
    if (m_job_xml_reader.hasError())
    {
        qDebug()<<"XML Error:"<< m_job_xml_reader.errorString();
        
    }
    file.close();
}

void JobEditModel::editXmlFile()
{
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
    m_blocks_data1.emplace(index, block);
}

QDomNode JobEditModel::createNodeIfNotExists(QDomNode &parent, QString name, QStringList attr_names, QStringList attr_value)
{
}

void JobEditModel::addEmptyBlock(int index)
{
    if (index < 0)
    {
        return;
    }
    m_blocks_data1.emplace(index, BlockData());
    int i = m_blocks_data1.size();
}

