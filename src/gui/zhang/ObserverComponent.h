#ifndef OBSERVER_COMPONENT_H
#define OBSERVER_COMPONENT_H

#include "ObserverPatternImp.h"

class ObserverComponent
{
public:
    ObserverComponent();
    void notify();
    void attach();
    void detach();
};

#endif // OBSERVER_COMPONENT_H
