#include "ObserverComponent.h"

ObserverComponent::ObserverComponent()
{
}

void ObserverComponent::notify()
{
}

void ObserverComponent::notify(const std::string)
{
}

void ObserverComponent::attach(const std::string key, std::shared_ptr<ObserverImp>)
{
}

std::shared_ptr<ObserverImp> ObserverComponent::detach(const std::string key)
{
    auto iter = m_observers.find(key);
    if (iter == m_observers.end())
    {
        return nullptr;
    }
    else
    {
        return iter->second;
    }
}
