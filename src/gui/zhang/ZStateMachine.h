#ifndef ZSTATEMACHINE_H
#define ZSTATEMACHINE_H
#include <QStateMachine>


class IdleQState:public QState
{
    Q_OBJECT
public:
    explicit IdleQState(QObject *parent);
protected:
    void onEntry(QEvent *event) override;
private:

};

class InitQState:public QState
{
    Q_OBJECT
public:
    explicit InitQState();
protected:
    void onEntry(QEvent *event) override;
private:

};

class ZQStateMachine:public QStateMachine
{
    Q_OBJECT
public:
    ZQStateMachine();
private:

};
#endif // !ZSTATEMACHINE_H
