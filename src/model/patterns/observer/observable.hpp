//#pragma once
#include <iostream>
#include <list>
#include <string>
#include "observer.hpp"

class MapObservable
{
public:
  ~MapObservable(){};
  void Attach(MapObserver *observer);
  void Detach(MapObserver *observer);
  void sendMessage(std::string key, std::string value);

private:
  std::list<MapObserver *> list_observer_;
};