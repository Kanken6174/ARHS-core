#include "observable.hpp"

void Observable::Attach(Observer *observer)
{
  list_observer_.push_back(observer);
}

void Observable::Detach(Observer *observer)
{
  list_observer_.remove(observer);
}

void Observable::sendMessage(std::string str)
{
  std::list<Observer*>::iterator iterator = list_observer_.begin();
  while (iterator != list_observer_.end())
  {
    (*iterator)->Update(str);
    ++iterator;
  }
}