#include "ZoneSetLoader.h"

ZoneSetLoader::ZoneSetLoader()
{
    //ctor
}

ZoneSetLoader::~ZoneSetLoader()
{
    //dtor
}

void ZoneSetLoader::load(std::string const& mapFilePath, ZoneSetLoader::ZoneSet & zoneMap) const
{
    std::ifstream zoneMapFile(mapFilePath);
    std::string line;

    /** @todo zone key MUST be unique */

    while(std::getline(zoneMapFile, line))
    {
        // Handling Windows edited files
        if ('\r' == *(line.cend()-1))
        {
            line.erase(line.end()-1);
        }

        std::istringstream streamLine(line);
        std::string cell;

        zoneMap.push_back(ZoneSetLoader::ZoneSetLine(0));
        while (std::getline(streamLine, cell, ';'))
        {
            zoneMap.rbegin()->push_back(cell);
        }
    }
}
