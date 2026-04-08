#ifndef LOG_SYSTEM_H
#define LOG_SYSTEM_H
#include<QObject>
    
class LogSystem:public QObject
{
    Q_OBJECT
public:
    explicit LogSystem();
signals:
    void sglAlarm();
private:
    
};

#endif // LOG_SYSTEM_H
