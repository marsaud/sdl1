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

    static const std::string ZONESET_FILE;

    void load(std::string const& zoneSetFilePath, ZoneSetLoader::ZoneSet & zoneSet) const;
protected:
private:
};

#endif // ZONESETLOADER_H
