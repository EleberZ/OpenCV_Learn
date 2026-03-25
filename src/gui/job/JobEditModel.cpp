#include "JobEditModel.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDomDocument>
#include <qfileinfo.h>

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
    QDomElement rootElement = m_job_xml.createElement(fileInfo.baseName());
    m_job_xml.appendChild(rootElement);
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

void JobEditModel::slotNewJob(QString filepath)
{
    NewJobFile(filepath);
    loadJobFile(filepath);
}

void JobEditModel::slotSaveJob()
{
    saveJobFile();
}

void JobEditModel::slotLoadJob(QString filepath)
{
    loadJobFile(filepath);
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
