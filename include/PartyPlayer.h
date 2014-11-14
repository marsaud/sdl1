#ifndef PARTYPLAYER_H
#define PARTYPLAYER_H

#include <string>

#include "common.h"
#include "StaticWorld.h"

class PartyPlayer
{
public:
    PartyPlayer(StaticWorld *world);
    virtual ~PartyPlayer();

    typedef std::vector<Tile> TileSetLine;
    typedef std::vector<PartyPlayer::TileSetLine> TileSet;
    typedef std::vector<std::string> ZoneSetLine;
    typedef std::vector<PartyPlayer::ZoneSetLine> ZoneSet;

    static void init();
    static void free();

    void process(Action & action);
    void move(Move & move);
protected:
private:
    static Movement *ms_movements;

    StaticWorld *m_world = NULL;
    Position m_tile;
    Position m_zone;
    std::string m_area;

    void m_link(Action & action);

    bool m_outOfSet(Position const& pos, PartyPlayer::TileSet const& tileSet) const;
    bool m_outOfSet(Position const& pos, PartyPlayer::ZoneSet const& zoneSet) const;
};

#endif // PARTYPLAYER_H
