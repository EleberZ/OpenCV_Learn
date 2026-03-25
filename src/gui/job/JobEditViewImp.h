#ifndef JOB_EDIT_VIEWLIMP_H
#define JOB_EDIT_VIEWLIMP_H

#include <QWidget>

//观察者
class JobEditViewImp:public QWidget
{
    Q_OBJECT
public:
    explicit JobEditViewImp(QWidget *parent = nullptr);
    virtual ~JobEditViewImp() = default;
    virtual void updateWidget() = 0;
private:

};

#endif // JOB_EDIT_VIEWLIMP_H
