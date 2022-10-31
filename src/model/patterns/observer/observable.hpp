#pragma once
#include <iostream>
#include <list>
#include <string>
#include "observer.hpp"

class Observable {
 public:
  ~Observable(){};
  void Attach(Observer *observer);
  void Detach(Observer *observer);
  void sendMessage(std::string str);
  private:
  std::list<Observer*> list_observer_;
};