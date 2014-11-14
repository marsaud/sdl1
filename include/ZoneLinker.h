#ifndef ZONELINKER_H
#define ZONELINKER_H

#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>

#include "common.h"

class ZoneLinker
{
    public:
        ZoneLinker(std::string const& filePath);
        virtual ~ZoneLinker();

        struct _zone_link
        {
            std::string tag;
            Position tile;
            Position zone;
            std::string targetSet;
            std::string targetLinkTag;
        };
        typedef struct _zone_link ZoneLink;

        static const std::string ZONE_LINK_FILE;

        const ZoneLinker::ZoneLink *find(Position const& zone, Position const& tile) const;
        const ZoneLinker::ZoneLink *find(std::string const& tag) const;

    protected:
    private:
        typedef std::unordered_map<std::string, ZoneLinker::ZoneLink> LinkMap;
        ZoneLinker::LinkMap m_loadedLinks;
};

#endif // ZONELINKER_H
