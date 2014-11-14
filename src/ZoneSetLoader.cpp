#include "ZoneSetLoader.h"

const std::string ZoneSetLoader::ZONESET_FILE = "zonemap.zm";

ZoneSetLoader::ZoneSetLoader()
{
    //ctor
}

ZoneSetLoader::~ZoneSetLoader()
{
    //dtor
}

void ZoneSetLoader::load(std::string const& zoneSetFilePath, ZoneSetLoader::ZoneSet & zoneSet) const
{
    std::ifstream zoneSetFile(zoneSetFilePath);
    std::string line;

    /** @todo zone key MUST be unique */

    while(std::getline(zoneSetFile, line))
    {
        // Handling Windows edited files
        if ('\r' == *(line.cend()-1))
        {
            line.erase(line.end()-1);
        }

        std::istringstream streamLine(line);
        std::string cell;

        zoneSet.push_back(ZoneSetLoader::ZoneSetLine(0));
        while (std::getline(streamLine, cell, ';'))
        {
            zoneSet.rbegin()->push_back(cell);
        }
    }
}
