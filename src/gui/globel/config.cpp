#include "config.h"
#include <QApplication>
#include <QSettings>

Config::Config()
    :m_config_file_path(QApplication::applicationDirPath() + "/" + "config/config.ini"),
    m_settings(m_config_file_path, QSettings::IniFormat),
    m_is_saved(true)
{
    loadConfig();
}

Config::~Config()
{
}

void Config::loadConfig()
{
    bool first_run = m_settings.value("first_run", false).toBool();
    if (!first_run)
    {
        m_camera_no = m_settings.value("camera_no", 0).toUInt();
        m_connect_type = m_settings.value("connect_type", 0).toUInt();
        m_camera_type = m_settings.value("camera_type", 0).toString();
        m_ip = m_settings.value("ip", "192.168.1.100").toString();

        m_camera_no = m_settings.value("exposure_time", 0).toUInt();
        m_iso = m_settings.value("iso", 0).toUInt();

        m_picture_template_path = m_settings.value("picture_template_path", "").toString();
        m_ok_path = m_settings.value("ok_path", "").toString();
        m_ng_path = m_settings.value("ng_path", "").toString();
        m_settings.setValue("first_run", true);
    }
}
void Config::saveConfig()
{
    m_is_saved = true;

    m_settings.setValue("camera_no", m_camera_no);
    m_settings.setValue("connect_type", m_connect_type);
    m_settings.setValue("camera_type", m_camera_type);
    m_settings.setValue("ip", m_ip);

    m_settings.setValue("exposure_time", m_exposure_time);
    m_settings.setValue("iso", m_iso);

    m_settings.setValue("picture_template_path", m_picture_template_path);
    m_settings.setValue("ok_path", m_ok_path);
    m_settings.setValue("ng_path", m_ng_path);

    m_settings.sync();
}
void Config::setCameraCount(int count)
{
    m_camera_count = count;
}
int Config::getCameraCount()
{
    return m_camera_count;
}
void Config::setConnectType(int index)
{
    m_is_saved = false;
    m_connect_type = index;
}

int Config::getConnectType()
{
    return m_connect_type;
}

void Config::setCameraType(QString name)
{
    m_is_saved = false;
    m_camera_type = name;
}

QString Config::getCameraType()
{
    return m_camera_type;
}

void Config::setIp(QString ip)
{
    m_is_saved = false;
    m_ip = ip;
}

QString Config::getIp()
{
    return m_ip;
}

void Config::setCameraNo(int no)
{
    m_is_saved = false;
    m_camera_no = no;
}

int Config::getCameraNo()
{
    return m_camera_no;
}

void Config::setExposureTime(int time)
{
    m_is_saved = false;
    m_exposure_time = time;
}

int Config::getExposureTime()
{
    return m_exposure_time;
}

void Config::setISO(int iso)
{
    m_is_saved = false;
    m_iso = iso;
}

int Config::getISO()
{
    return m_iso;
}

void Config::setPictureTemplatePath(const QString &path)
{
    m_is_saved = false;
    m_picture_template_path = path;
}

QString Config::getPictureTemplatePath()
{
    
    return m_picture_template_path;
}

void Config::setOKPath(const QString &path)
{
    m_is_saved = false;
    m_ok_path = path;
}

QString Config::getOKPath()
{
    return m_ok_path;
}

void Config::setNGPath(const QString &path)
{
    m_is_saved = false;
    m_ng_path = path;
}

QString Config::getNGPath()
{
    return m_ng_path;
}
