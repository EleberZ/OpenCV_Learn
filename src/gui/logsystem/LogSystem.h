#ifndef LOG_SYSTEM_H
#define LOG_SYSTEM_H
#include<QObject>
#include<QFile>
#include <QString>
#include <QStringList>


class LogSystem:public QObject
{
    Q_OBJECT
public:
    static LogSystem* getInstance();
    //void alarm(const QString &str);
    //void warning(const QString &str);
    //void info(const QString &str);
    void output(const QString &str);
    void addLogType(const QString &str);
    void RecordLog(const QString &type, const QString &log);
signals:
    //void sglAlarm();
    //void sglWarning();
    //void sglInfo();
    void sglOutput(const QString &str);
public:
    QStringList m_log_type;
private:
    int m_i;
    static LogSystem *m_instance;
    explicit LogSystem();
    QString m_log_path;
};

#endif // LOG_SYSTEM_H
