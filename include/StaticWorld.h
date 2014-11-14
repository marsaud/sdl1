#ifndef STATICWORLD_H
#define STATICWORLD_H

#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>

#include "StaticArea.h"

class StaticWorld
{
public:
    StaticWorld(std::string const& scenario, std::string const& dataDir);
    virtual ~StaticWorld();

    typedef std::unordered_map<std::string,StaticArea*> AreaMapping;

    const static std::string SCN_BOOT_FILE;

    const StaticArea* getArea(std::string const& key);
    std::string getStartArea() const;

protected:
private:
    std::string m_dir;
    std::string m_scenario;
    std::string m_startArea;
    StaticWorld::AreaMapping m_loadedAreas;

    void m_bootWorld();
    void m_loadArea(std::string const& key);
};

#endif // STATICWORLD_H
