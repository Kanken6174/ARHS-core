#include "observable.hpp"

void MapObservable::Attach(MapObserver *observer)
{
  list_observer_.push_back(observer);
}

void MapObservable::Detach(MapObserver *observer)
{
  list_observer_.remove(observer);
}

void MapObservable::sendMessage(std::string key, std::string value)
{
  std::list<MapObserver*>::iterator iterator = list_observer_.begin();
  while (iterator != list_observer_.end())
  {
    (*iterator)->Update(key, value);
    ++iterator;
  }
}