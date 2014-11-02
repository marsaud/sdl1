#ifndef ZONESETLOADER_H
#define ZONESETLOADER_H

#include <fstream>
#include <string>
#include <sstream>
#include <vector>

class ZoneSetLoader
{
    public:
        ZoneSetLoader();
        virtual ~ZoneSetLoader();

        typedef std::vector<std::vector<std::string> > ZoneSet;

        void load(std::string const& mapFilePath, ZoneSetLoader::ZoneSet & zoneMap);
    protected:
    private:
};

#endif // ZONESETLOADER_H
