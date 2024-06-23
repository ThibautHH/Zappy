/*
** EPITECH PROJECT, 2024
** Zappy GUI
** File description:
** Zappy::GUI::Event
*/

#include "Event.hpp"
#include "GameState.hpp"

using namespace Zappy::GUI;

template<>
Event::Traits::from_string_type Event::Traits::from_string = {
    { "msz", Event::Type::MAP_SIZE },
    { "tna", Event::Type::TEAM_NAME },
    { "bct", Event::Type::TILE_CONTENT },
    { "pnw", Event::Type::PLAYER_NEW },
    { "ppo", Event::Type::PLAYER_POSITION },
    { "plv", Event::Type::PLAYER_LEVEL },
    { "pin", Event::Type::PLAYER_INVENTORY },
    { "pex", Event::Type::PLAYER_EJECTED },
    { "pbc", Event::Type::PLAYER_BROADCAST },
    { "pic", Event::Type::PLAYER_INCANTATION_START },
    { "pie", Event::Type::PLAYER_INCANTATION_END },
    { "pgr", Event::Type::PLAYER_DROP },
    { "pgt", Event::Type::PLAYER_COLLECT },
    { "pdi", Event::Type::PLAYER_DEATH },
    { "pfk", Event::Type::PLAYER_LAY },
    { "enw", Event::Type::EGG_LAID },
    { "ebo", Event::Type::EGG_HATCH },
    { "edi", Event::Type::EGG_DIE },
    { "seg", Event::Type::GAME_END },
    { "sgt", Event::Type::FREQUENCY_GET },
    { "sst", Event::Type::FREQUENCY_SET },
    { "smg", Event::Type::SERVER_MESSAGE },
    { "suc", Event::Type::COMMAND_UNKNOWN },
    { "sbp", Event::Type::COMMAND_INVALID }
};

static const Event::Type valid_values[] = {
    Event::Type::MAP_SIZE,
    Event::Type::TEAM_NAME,
    Event::Type::TILE_CONTENT,
    Event::Type::PLAYER_NEW,
    Event::Type::PLAYER_POSITION, Event::Type::PLAYER_LEVEL, Event::Type::PLAYER_INVENTORY,
    Event::Type::PLAYER_EJECTED,
    Event::Type::PLAYER_BROADCAST,
    Event::Type::PLAYER_INCANTATION_START, Event::Type::PLAYER_INCANTATION_END,
    Event::Type::PLAYER_DROP, Event::Type::PLAYER_COLLECT,
    Event::Type::PLAYER_DEATH,
    Event::Type::PLAYER_LAY, Event::Type::EGG_LAID,
    Event::Type::EGG_HATCH, Event::Type::EGG_DIE,
    Event::Type::GAME_END,
    Event::Type::FREQUENCY_GET, Event::Type::FREQUENCY_SET,
    Event::Type::SERVER_MESSAGE,
    Event::Type::COMMAND_UNKNOWN, Event::Type::COMMAND_INVALID
};

template<>
Event::Traits::valid_values_type Event::Traits::valid_values = ::valid_values;

const Event::ParsersMap Event::Parsers = {
    { Event::Type::MAP_SIZE, [](std::istream &is, Event &event) { is >> event._vector; } },
    { Event::Type::TEAM_NAME, [](std::istream &is, Event &event) { is >> event._message; } },
    { Event::Type::TILE_CONTENT, [](std::istream &is, Event &event) { is >> event._vector >> event._inventory; } },
    { Event::Type::PLAYER_NEW, [](std::istream &is, Event &event) { is >> Id{event._id} >> event._vector >> event._orientation >> event._number >> event._message; } },
    { Event::Type::PLAYER_POSITION, [](std::istream &is, Event &event) { is >> Id{event._id} >> event._vector >> event._orientation; } },
    { Event::Type::PLAYER_LEVEL, [](std::istream &is, Event &event) { is >> Id{event._id} >> event._number; } },
    { Event::Type::PLAYER_INVENTORY, [](std::istream &is, Event &event) { is >> Id{event._id} >> event._inventory; } },
    { Event::Type::PLAYER_EJECTED, [](std::istream &is, Event &event) { is >> Id{event._id}; } },
    { Event::Type::PLAYER_BROADCAST, [](std::istream &is, Event &event) { is >> Id{event._id} >> event._message; } },
    { Event::Type::PLAYER_INCANTATION_START, [](std::istream &is, Event &event) { is >> event._vector >> event._number >> Id{event._id}; } },
    { Event::Type::PLAYER_INCANTATION_END, [](std::istream &is, Event &event) { is >> event._vector >> event._message; } },
    { Event::Type::PLAYER_DROP, [](std::istream &is, Event &event) { is >> Id{event._id} >> event._number; } },
    { Event::Type::PLAYER_COLLECT, [](std::istream &is, Event &event) { is >> Id{event._id} >> event._number; } },
    { Event::Type::PLAYER_DEATH, [](std::istream &is, Event &event) { is >> Id{event._id}; } },
    { Event::Type::PLAYER_LAY, [](std::istream &is, Event &event) { is >> Id{event._id}; } },
    { Event::Type::EGG_LAID, [](std::istream &is, Event &event) { is >> Id{event._id} >> Id{event._number} >> event._vector; } },
    { Event::Type::EGG_HATCH, [](std::istream &is, Event &event) { is >> Id{event._id}; } },
    { Event::Type::EGG_DIE, [](std::istream &is, Event &event) { is >> Id{event._id}; } },
    { Event::Type::GAME_END, [](std::istream &is, Event &event) { is >> event._message; } },
    { Event::Type::FREQUENCY_GET, [](std::istream &is, Event &event) { is >> event._number; } },
    { Event::Type::FREQUENCY_SET, [](std::istream &is, Event &event) { is >> event._number; } },
    { Event::Type::SERVER_MESSAGE, [](std::istream &is, Event &event) { is >> event._message; } },
    { Event::Type::COMMAND_UNKNOWN, [](std::istream &, Event &) {} },
    { Event::Type::COMMAND_INVALID, [](std::istream &, Event &) {} }
};

const Event::UpdatersMap Event::Updaters = {
    { Event::Type::MAP_SIZE, [](const Event &event, GameState &gameState) { gameState.setSize(event._vector); } },
    { Event::Type::TEAM_NAME, [](const Event &event, GameState &gameState) { gameState.addTeam(std::move(event._message)); } },
    { Event::Type::TILE_CONTENT, [](const Event &event, GameState &gameState) { gameState.updateTile(event._vector, event._inventory); } },
    { Event::Type::PLAYER_NEW, [](const Event &event, GameState &gameState) { gameState.addPlayer(event._id, event._vector, event._orientation, event._number, std::move(event._message)); } },
    { Event::Type::PLAYER_POSITION, [](const Event &event, GameState &gameState) { gameState.updatePlayerPosition(event._id, event._vector, event._orientation); } },
    { Event::Type::PLAYER_LEVEL, [](const Event &event, GameState &gameState) { gameState.updatePlayerLevel(event._id, event._number); } },
    { Event::Type::PLAYER_INVENTORY, [](const Event &event, GameState &gameState) { gameState.updatePlayerInventory(event._id, event._inventory); } },
    { Event::Type::PLAYER_EJECTED, [](const Event &event, GameState &gameState) { gameState.ejectPlayer(event._id); } },
    { Event::Type::PLAYER_BROADCAST, [](const Event &event, GameState &gameState) { gameState.message(std::move(event._message), event._id); } },
    { Event::Type::PLAYER_INCANTATION_START, [](const Event &event, GameState &gameState) { gameState.startIncantation(event._vector, event._number, {event._id}); } },
    { Event::Type::PLAYER_INCANTATION_END, [](const Event &event, GameState &gameState) { gameState.endIncantation(event._vector, std::move(event._message)); } },
    { Event::Type::PLAYER_DROP, [](const Event &event, GameState &gameState) { gameState.updatePlayerInventory(event._id, event._inventory); } },
    { Event::Type::PLAYER_COLLECT, [](const Event &event, GameState &gameState) { gameState.updatePlayerInventory(event._id, event._inventory); } },
    { Event::Type::PLAYER_DEATH, [](const Event &event, GameState &gameState) { gameState.playerDies(event._id); } },
    { Event::Type::PLAYER_LAY, [](const Event &event, GameState &gameState) {} },
    { Event::Type::EGG_LAID, [](const Event &event, GameState &gameState) { gameState.addEgg(event._id, event._number, event._vector); } },
    { Event::Type::EGG_HATCH, [](const Event &event, GameState &gameState) { gameState.eggHatches(event._id); } },
    { Event::Type::EGG_DIE, [](const Event &event, GameState &gameState) { gameState.eggDies(event._id); } },
    { Event::Type::GAME_END, [](const Event &event, GameState &gameState) { gameState.endGame(std::move(event._message)); } },
    { Event::Type::FREQUENCY_GET, [](const Event &event, GameState &gameState) { gameState.setTimeUnit(event._number); } },
    { Event::Type::FREQUENCY_SET, [](const Event &, GameState &) {} },
    { Event::Type::SERVER_MESSAGE, [](const Event &event, GameState &gameState) { gameState.message(std::move(event._message)); } },
    { Event::Type::COMMAND_UNKNOWN, [](const Event &, GameState &) {} },
    { Event::Type::COMMAND_INVALID, [](const Event &, GameState &) {} }
};

void Event::update(GameState &gameState) const
{
    Updaters.at(type)(*this, gameState);
}
