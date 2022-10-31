#include <iostream>
#include <list>
#include <string>
#include "observer.hpp"

class Observable {
 public:
  ~Observable(){};
  void Attach(Observer *observer) = 0;
  void Detach(Observer *observer) = 0;
  void sendMessage(std::string str);
  private:
  std::list<Observer*> list_observer_;
};