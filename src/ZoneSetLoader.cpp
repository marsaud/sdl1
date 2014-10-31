#include "ZoneSetLoader.h"

ZoneSetLoader::ZoneSetLoader()
{
    //ctor
}

ZoneSetLoader::~ZoneSetLoader()
{
    //dtor
}

void ZoneSetLoader::load()
{
    std::ifstream zoneMapFile("data/scenario1/zonemap.txt");
    std::vector<std::vector<std::string> > zoneMap;
    std::string line;

    while(std::getline(zoneMapFile, line))
    {
        std::istringstream streamLine(line);
        std::string cell;

        zoneMap.push_back(std::vector<std::string>(0));
        while (std::getline(streamLine, cell))
        {
            zoneMap.rbegin()->push_back(cell);
        }
    }
}
