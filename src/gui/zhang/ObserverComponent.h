#ifndef OBSERVER_COMPONENT_H
#define OBSERVER_COMPONENT_H

#include "ObserverPatternImp.h"
#include <map>
#include <string>
#include <memory>

class ObserverComponent
{
public:
    ObserverComponent();
    void notify();
    void notify(const std::string);
    void attach(const std::string key, std::shared_ptr<ObserverImp> observer);
    std::shared_ptr<ObserverImp> detach(const std::string key);
private:
    std::map<std::string, std::shared_ptr<ObserverImp>> m_observers;
};

#endif // OBSERVER_COMPONENT_H
