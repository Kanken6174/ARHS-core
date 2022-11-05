#include <string>

class MapObserver {
 public:
  virtual void Update(const std::string &key, const std::string &value) = 0;
};