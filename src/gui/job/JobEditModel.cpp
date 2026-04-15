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

void BlockData::setTemplateMatchType(cv::TemplateMatchModes methor)
{
    m_template_match_type = methor;
}

cv::TemplateMatchModes BlockData::getTemplateMatchType()
{
    return m_template_match_type;
}

void BlockData::setMatchMethod(int match_method)
{
    m_match_method = match_method;
}

int BlockData::getMatchMethod()
{
    return m_match_method;
}

JobEditModel::JobEditModel(QObject *parent)
{
    //m_blocks_data1 = new std::map<int, BlockData>();
    m_job_file = nullptr;
    m_dtd = R"(
    <!DOCTYPE job[
        <!ELEMENT job (blockCount, Block*)>
        <!ATTLIST job id ID #REQUIRED >
        <!ELEMENT blockCount (#PCDATA)>
        <!ATTLIST blockCount id ID #REQUIRED >
        <!ELEMENT Block (Position, MaskPath, TempPath)>
        <!ATTLIST Block id ID #REQUIRED >
        <!ELEMENT MaskPath (#PCDATA)>
        <!ATTLIST MaskPath id ID #REQUIRED >
        <!ELEMENT TempPath (#PCDATA)>
        <!ATTLIST TempPath id ID #REQUIRED >
        <!ELEMENT Position EMPTY>
        <!ATTLIST Position id ID #REQUIRED x CDATA #REQUIRED y CDATA #REQUIRED >
    ]>
)";
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
    QFileInfo fileInfo(filepath);
    QFile file(filepath);
    if (fileInfo.exists())
    {
        return false;
    }
    if (!file.open(QIODevice::ReadWrite))
    {
        return false;
    }
    m_job_xml_writer.setDevice(&file);
    m_job_xml_writer.setAutoFormatting(true);
    m_job_xml_writer.writeStartDocument("1.0", "UTF-8");
    m_job_xml_writer.writeDTD(m_dtd);

    m_job_xml_writer.writeStartElement("job");
    m_job_xml_writer.writeAttribute("id", fileInfo.baseName());
    m_job_xml_writer.writeAttribute("xmlns:xsi", m_xsi);
    m_job_xml_writer.writeAttribute("xmlns:xs", m_xs);

    m_job_xml_writer.writeStartElement("blockCount");
    m_job_xml_writer.writeAttribute("id", "blockCount");
    m_job_xml_writer.writeAttribute("type", "int");
    m_job_xml_writer.writeCharacters("0");
    m_job_xml_writer.writeEndElement();

    m_job_xml_writer.writeEndElement();
    m_job_xml_writer.writeEndDocument();

    file.close();
    return true;
}

void JobEditModel::loadJobFile(QString filepath)
{
    m_filepath = filepath;
    QFileInfo fileInfo(filepath);
    QFile file(filepath);
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
        m_job_xml_reader.readNext();
        if (m_job_xml_reader.isStartElement())
        {
            continue;
        }

        if (m_job_xml_reader.name() == "blockCount")
        {

        }
        else if (m_job_xml_reader.name() == "Block")
        {

        }
        else if (m_job_xml_reader.name() == "Position")
        {

        }
        else if (m_job_xml_reader.name() == "MaskPath")
        {

        }
        else if (m_job_xml_reader.name() == "TempPath")
        {

        }
    }



    file.close();
    //TODO:需要添加更新job_xml的功能
    emit sglloadJobFileSuccess();
}

void JobEditModel::saveJobFile()
{
    QString str = m_filepath;
    QFile file(m_filepath);
    if (!file.open(QIODevice::ReadWrite))
    {
        return;
    }
    QTextStream out(&file);
    file.close();
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

int JobEditModel::getBlockCount()
{
    return m_blocks_data1.size();
}

void JobEditModel::setCurrentBlockIndex(int index)
{
    m_current_block_index = index;
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
    NewJobFile(filepath);
    loadJobFile(filepath);
}

void JobEditModel::slotLoadJob(QString filepath)
{
    loadJobFile(filepath);
}

void JobEditModel::slotBlockSave()
{
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

void JobEditModel::createDTD()
{
    QString dtdContent;



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
    //QDomNodeList childNodes = parent.childNodes();
    //QDomNode elem;
    //bool exist = false;
    //for (int i = 0; i < childNodes.count(); i++)
    //{
    //    elem = childNodes.at(i).toElement();
    //    exist = (elem.nodeName() == name) || exist;
    //    if (exist)
    //    {
    //        break;
    //    }
    //    else
    //    {
    //        continue;
    //    }
    //}
    //if (!exist)
    //{
    //    elem = m_job_xml.createElement(name);
    //    parent.appendChild(elem);
    //}
    //int i = 0;
    //for (auto str : attr_names)
    //{
    //    elem.toElement().setAttribute(str, attr_value[i]);
    //    i++;
    //}
    //return elem;
}

void JobEditModel::addEmptyBlock(int index)
{
    if (index < 0)
    {
        return;
    }
    m_blocks_data1.emplace(index, BlockData());

}

