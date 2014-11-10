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

    typedef std::vector<std::string> ZoneSetLine;
    typedef std::vector<ZoneSetLoader::ZoneSetLine> ZoneSet;

    void load(std::string const& mapFilePath, ZoneSetLoader::ZoneSet & zoneMap) const;
protected:
private:
};

#endif // ZONESETLOADER_H
