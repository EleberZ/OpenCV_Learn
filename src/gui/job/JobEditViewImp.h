#ifndef JOB_EDIT_VIEWLIMP_H
#define JOB_EDIT_VIEWLIMP_H

#include <QWidget>

//观察者
class JobEditViewImp:public QWidget
{
    Q_OBJECT
public:
    explicit JobEditViewImp(QWidget *parent = nullptr);
    //virtual ~JobEditViewImp() = default;
    template<typename T>
    inline void updateWidget(T data);
    virtual void initWidget() = 0;
public slots:
    virtual void slotNotifyJobEditView() = 0;
private:

};

#endif // JOB_EDIT_VIEWLIMP_H

//template<typename T>
//void JobEditViewImp::updateWidget(T data)
//{
//    //TODO:需要实现页面更新
//}
