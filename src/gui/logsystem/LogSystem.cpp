#include "LogSystem.h"
#include <QApplication>
#include <QDateTime>

LogSystem *LogSystem::getInstance()
{
    static LogSystem instance;
    return &instance;
}

void LogSystem::alarm(const QString &str)
{
    QDateTime time;
    QString str_time_y = time.currentDateTime().toString("yyyy");
    QString str_time_m = time.currentDateTime().toString("MM");
    QString str_time_d = time.currentDateTime().toString("dd");
    QString str_time_time = time.currentDateTime().toString("hh:mm:ss");
    QFile file(m_log_path+"/alarm/"+str_time_y+"/"+ str_time_m +"/" + str_time_d + ".log");
    if (!file.open(QIODevice::ReadWrite))
    {
        return;
    }
    QString str_log = str_time_time + ">alarm>" + str + "\n";
    file.write(str_log.toUtf8());
    file.close();
    output(str_log);
}

void LogSystem::warning(const QString &str)
{
    QDateTime time;
    QString str_time_y = time.currentDateTime().toString("yyyy");
    QString str_time_m = time.currentDateTime().toString("MM");
    QString str_time_d = time.currentDateTime().toString("dd");
    QString str_time_time = time.currentDateTime().toString("hh:mm:ss");
    QFile file(m_log_path + "/warning/" + str_time_y + "/" + str_time_m + "/" + str_time_d + ".log");
    if (!file.open(QIODevice::ReadWrite))
    {
        return;
    }
    QString str_log = str_time_time + ">warning>" + str + "\n";
    file.write(str_log.toUtf8());
    file.close();
    output(str_log);
}

void LogSystem::info(const QString &str)
{
    QDateTime time;
    QString str_time_y = time.currentDateTime().toString("yyyy");
    QString str_time_m = time.currentDateTime().toString("MM");
    QString str_time_d = time.currentDateTime().toString("dd");
    QString str_time_time = time.currentDateTime().toString("hh:mm:ss");
    QFile file(m_log_path + "/info/" + str_time_y + "/" + str_time_m + "/" + str_time_d + ".log");
    if (!file.open(QIODevice::ReadWrite))
    {
        return;
    }
    QString str_log = str_time_time + ">alarm>" + str + "\n";
    file.write(str_log.toUtf8());
    file.close();
    output(str_log);
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


LogSystem::LogSystem(): m_log_path(QApplication::applicationDirPath() + "/log")
{
}
