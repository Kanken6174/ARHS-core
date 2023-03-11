#include "Plugin.hpp"
#include <map>
class Pipeline;

class PluginManager{
    public:
    std::map<std::string, Plugin*> plugins;
    PluginManager(Pipeline& p);
};