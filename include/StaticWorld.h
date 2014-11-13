#ifndef STATICWORLD_H
#define STATICWORLD_H

#include <string>
#include <unordered_map>

#include "StaticArea.h"

class StaticWorld
{
public:
    StaticWorld(std::string const& scenario, std::string const& scenarioDirPath);
    virtual ~StaticWorld();

    typedef std::unordered_map<std::string,StaticArea*> AreaMapping;

protected:
private:
    std::string m_scenario;
    StaticWorld::AreaMapping m_loadedAreas;
};

#endif // STATICWORLD_H
