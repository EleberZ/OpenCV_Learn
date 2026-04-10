#include "LogSystem.h"
#include <QApplication>
#include <QDateTime>

LogSystem *LogSystem::getInstance()
{
    static LogSystem instance;
    return &instance;
}

void LogSystem::output(const QString &str)
{
    QDateTime time;
    QString str_time_y = time.currentDateTime().toString("yyyy");
    QString str_time_m = time.currentDateTime().toString("MM");
    QString str_time_d = time.currentDateTime().toString("dd");
    QString str_time_time = time.currentDateTime().toString("hh:mm:ss");
    QFile file(m_log_path + "/output/" + str_time_y + "/" + str_time_m + "/" + str_time_d + ".log");
    if (!file.open(QIODevice::ReadWrite))
    {
        return;
    }
    file.write(str.toUtf8());
    file.close();
    emit sglOutput(str);
}

void LogSystem::addLogType(const QString &str)
{
    QStringList list;
    if (!m_log_type.contains(str))
    {
        m_log_type<<str;
        list.append(str);
    }
}

void LogSystem::RecordLog(const QString &type, const QString &log)
{
    if (m_log_type.contains(type))
    {
        QDateTime time;
        QString str_time_y = time.currentDateTime().toString("yyyy");
        QString str_time_m = time.currentDateTime().toString("MM");
        QString str_time_d = time.currentDateTime().toString("dd");
        QString str_time_time = time.currentDateTime().toString("hh:mm:ss");
        QFile file(m_log_path + "/" + type + "/" + str_time_y + "/" + str_time_m + "/" + str_time_d + ".log");
        if (!file.open(QIODevice::ReadWrite))
        {
            return;
        }
        QString str_log = str_time_time + ">" + type + ">" + log + "\n";
        file.write(str_log.toUtf8());
        file.close();
        output(str_log);
    }
}

LogSystem::LogSystem():
    m_log_path(QApplication::applicationDirPath() + "/log")
{
    //m_log_type<<"alarm"<<"warning"<<"info"<<"output";
}
