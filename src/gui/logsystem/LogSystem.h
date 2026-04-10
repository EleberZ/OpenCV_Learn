#ifndef LOG_SYSTEM_H
#define LOG_SYSTEM_H
#include<QObject>
#include<QFile>

class LogSystem:public QObject
{
    Q_OBJECT
public:
    static LogSystem* getInstance();
    void alarm(const QString &str);
    void warning(const QString &str);
    void info(const QString &str);
    void output(const QString &str);
signals:
    void sglAlarm();
    void sglWarning();
    void sglInfo();
    void sglOutput(const QString &str);
private:
    static LogSystem *m_instance;
    explicit LogSystem();

    QString m_log_path;
};

#endif // LOG_SYSTEM_H
