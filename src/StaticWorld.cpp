#include "StaticWorld.h"

const std::string StaticWorld::SCN_BOOT_FILE = "boot.scn";

StaticWorld::StaticWorld(std::string const& scenario, std::string const& dataDir)
{
    m_dir = dataDir;
    m_scenario = scenario;
    m_loadedAreas.clear();

    m_bootWorld();
}

StaticWorld::~StaticWorld()
{
    for (StaticWorld::AreaMapping::iterator it = m_loadedAreas.begin(); m_loadedAreas.end() != it; ++it)
    {
        delete (it->second);
    }
    m_loadedAreas.clear();
}

const StaticArea* StaticWorld::getArea(std::string const& key)
{
    StaticWorld::AreaMapping::const_iterator it = m_loadedAreas.find(key);

    if (m_loadedAreas.cend() == it)
    {
        m_loadArea(key);
        it = m_loadedAreas.find(key);
    }

    return it->second;
}

void StaticWorld::m_loadArea(std::string const& key)
{
    m_loadedAreas[key] = new StaticArea(key, m_dir + "/" + m_scenario);
}

void StaticWorld::m_bootWorld()
{
    std::ifstream bootFile(m_dir + "/" + m_scenario + "/" + StaticWorld::SCN_BOOT_FILE);
    std::string line;

    /** @todo All here is to secure */

    while(std::getline(bootFile, line))
    {
        /** @todo share */
        if ('\r' == *(line.cend()-1))
        {
            line.erase(line.end()-1);
        }

        std::stringstream streamLine(line);
        std::string word;

        streamLine >> word;
        if ("start" == word)
        {
            streamLine >> m_startArea;
        }
        else
        {
            /** @todo throw exception */
        }
    }

    bootFile.close();
}

std::string StaticWorld::getStartArea() const
{
    return m_startArea;
}
