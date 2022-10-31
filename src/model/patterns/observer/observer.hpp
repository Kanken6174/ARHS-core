#include <string>

class Observer {
 public:
  virtual void Update(const std::string &message_from_subject) = 0;
};