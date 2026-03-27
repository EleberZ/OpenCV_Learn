#ifndef OBSERVER_PATTERN_IMP_H
#define OBSERVER_PATTERN_IMP_H

class ObserverImp
{
public:
    ObserverImp();
    virtual void update() = 0;

private:

};

class ObservableImp
{
public:
    ObservableImp();
    virtual void notify() = 0;
    virtual void attach() = 0;
    virtual void detach() = 0;

private:

};

#endif // OBSERVER_PATTERN_IMP_H
