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
    QTextStream out(&file);
    m_job_xml.clear();
    QDomProcessingInstruction xmlDecl = m_job_xml.createProcessingInstruction(
        "xml", "version='1.0' encoding='UTF-8'"
    );
    QString xs = "http://www.w3.org/2001/XMLSchema";
    QString xsi = "http://www.w3.org/2001/XMLSchema-instance";
    QDomElement rootElement = m_job_xml.createElement("job");
    rootElement.setAttribute("xmlns:xs", xs);
    rootElement.setAttribute("xmlns:xsi", xsi);
    rootElement.setAttribute("xsi:schemaLocation",
        xsi + " ./schemes/XMLSchema-instance.xsd " + xs + " ./schemes/XMLSchema.xsd");

    rootElement.setAttribute("id", fileInfo.baseName());
    QDomElement block_count = m_job_xml.createElement("blockCount");
    block_count.setAttribute("id", "blockCount");
    block_count.setAttribute("type", "int");
    block_count.appendChild(m_job_xml.createTextNode("0"));

    rootElement.appendChild(block_count);

    m_job_xml.appendChild(xmlDecl);
    m_job_xml.appendChild(rootElement);
    m_job_xml.save(out, 4);
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
    if (!m_job_xml.setContent(&file))
    {
        return;
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
    m_job_xml.save(out, 4);
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
    //if (!m_blocks_data.empty()
    //    && m_blocks_data.size() > index)
    //{
    //    return m_blocks_data[index];
    //}
    //else
    //{
    //    return BlockData();
    //}
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
    QDomElement  elem = m_job_xml.firstChildElement("job");
    QStringList attr_names, attr_values;
    attr_names << "match_method" << "method_type" << "x" << "y";
    //attr_value <<
    auto it = m_blocks_data1.find(m_current_block_index);
    if (it == m_blocks_data1.end())
    {
        return;
    }
    BlockData block = it->second;

    attr_values
        << QString::number(block.getMatchMethod())
        << QString::number(block.getTemplateMatchType())
        << QString::number(block.getXpos())
        << QString::number(block.getYpos());

    QDomElement block_elem = m_job_xml.createElement("block"+QString::number(m_current_block_index));
    for (auto attr_name: attr_names)
    {
        block_elem.setAttribute(attr_name, attr_values.at(attr_names.indexOf(attr_name)));
    }
    QDomElement mask_path = m_job_xml.createElement("mask_path");
    QDomElement temp_path = m_job_xml.createElement("temp_path");
    block_elem.appendChild(mask_path);
    block_elem.appendChild(temp_path);

    QDomText mask_text = m_job_xml.createTextNode(block.getMaskPicturePath());
    QDomText temp_text = m_job_xml.createTextNode(block.getTempPicturePath());
    mask_path.appendChild(mask_text);
    temp_path.appendChild(temp_text);

    //m_job_xml.save();
}

void JobEditModel::slotSaveJob()
{
    QFileInfo fileInfo(m_filepath);
    QDomElement root_elem = m_job_xml.elementById(fileInfo.baseName());
    for (auto block:m_blocks_data1)
    {
        QDomElement elem = m_job_xml.createElement("block");
        elem.setAttribute("id", "block" + QString::number(block.first));
        QDomElement match_method = m_job_xml.createElement("match_method");
        match_method.appendChild(m_job_xml.createTextNode(QString::number(block.second.getMatchMethod())));
        QDomElement method_type = m_job_xml.createElement("method_type");
        method_type.appendChild(m_job_xml.createTextNode(QString::number(block.second.getMatchMethod())));
        QDomElement position = m_job_xml.createElement("position");
        position.setAttribute("x", QString::number(block.second.getXpos()));
        position.setAttribute("y", QString::number(block.second.getYpos()));
        QDomElement temp_path = m_job_xml.createElement("temp_path");
        temp_path.appendChild(m_job_xml.createTextNode(block.second.getTempPicturePath()));
        QDomElement mask_path = m_job_xml.createElement("mask_path");
        mask_path.appendChild(m_job_xml.createTextNode(block.second.getMaskPicturePath()));
        elem.appendChild(match_method);
        elem.appendChild(method_type);
        elem.appendChild(position);
        elem.appendChild(temp_path);
        elem.appendChild(mask_path);

        root_elem.appendChild(elem);
    }
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
    QDomNodeList childNodes = parent.childNodes();
    QDomNode elem;
    bool exist = false;
    for (int i = 0; i < childNodes.count(); i++)
    {
        elem = childNodes.at(i).toElement();
        exist = (elem.nodeName() == name) || exist;
        if (exist)
        {
            break;
        }
        else
        {
            continue;
        }
    }
    if (!exist)
    {
        elem = m_job_xml.createElement(name);
        parent.appendChild(elem);
    }
    int i = 0;
    for (auto str : attr_names)
    {
        elem.toElement().setAttribute(str, attr_value[i]);
        i++;
    }
    return elem;
}

void JobEditModel::addEmptyBlock(int index)
{
    if (index < 0)
    {
        return;
    }
    m_blocks_data1.emplace(index, BlockData());

}

