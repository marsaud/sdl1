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
        std::istringstream streamLine(line);
        std::string cell;

        zoneMap.push_back(ZoneSetLoader::ZoneSetLine(0));
        while (std::getline(streamLine, cell, ';'))
        {
            if ('\r' == *(cell.cend()-1))
            {
                cell.erase(cell.end()-1);
            }
            zoneMap.rbegin()->push_back(cell);
        }
    }
}
