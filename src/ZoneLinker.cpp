#include "ZoneLinker.h"

const std::string ZoneLinker::ZONE_LINK_FILE = "zone.links";

ZoneLinker::ZoneLinker(std::string const& filePath)
{
    m_loadedLinks.clear();

    std::ifstream linkFile(filePath);
    std::string line;

    while (std::getline(linkFile, line))
    {
        if ('\r' == *(line.cend()-1))
        {
            line.erase(line.end()-1);
        }

        std::stringstream streamLine(line);
        ZoneLinker::ZoneLink link;

        streamLine >> link.tag;
        streamLine >> link.zone.x;
        streamLine >> link.zone.y;
        streamLine >> link.tile.x;
        streamLine >> link.tile.y;
        streamLine >> link.targetSet;
        streamLine >> link.targetLinkTag;

        m_loadedLinks[link.tag] = link;
    }
}

ZoneLinker::~ZoneLinker()
{
    //dtor
}

const ZoneLinker::ZoneLink* ZoneLinker::find(Position const& zone, Position const& tile) const
{
    const ZoneLinker::ZoneLink* ptr = NULL;

    for (ZoneLinker::LinkMap::const_iterator it = m_loadedLinks.cbegin(); m_loadedLinks.cend() != it; ++it)
    {
        if ((zone == it->second.zone) && (tile == it->second.tile))
        {
            ptr = &(it->second);
        }
    }

    return ptr;
}

const ZoneLinker::ZoneLink* ZoneLinker::find(std::string const& tag) const
{
    const ZoneLinker::ZoneLink* ptr = NULL;

    if (m_loadedLinks.find(tag) != m_loadedLinks.cend())
    {
        ptr = &(m_loadedLinks.find(tag)->second);
    }

    return ptr;
}
