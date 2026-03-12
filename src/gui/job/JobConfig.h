#ifndef JOB_CONFIG_H
#define JOB_CONFIG_H

#include<QWidget>

class JobConfig : public QWidget
{
    Q_OBJECT
public:
    explicit JobConfig(QWidget *parent = nullptr);
    ~JobConfig();
    void initWidget();
private:



};

#endif