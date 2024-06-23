/*
** EPITECH PROJECT, 2024
** Zappy GUI
** File description:
** Zappy::GUI::GameState
*/

#include "utils/enum_traits.hpp"

#include "GameState.hpp"

using namespace Zappy::GUI;

using OrientationTraits = utils::enum_traits<Orientation>;

template<>
OrientationTraits::from_string_type OrientationTraits::from_string = {
    {"North", Orientation::NORTH},
    {"East", Orientation::EAST},
    {"South", Orientation::SOUTH},
    {"West", Orientation::WEST}
};

static const Orientation valid_values[] = {
    Orientation::NORTH, Orientation::EAST, Orientation::SOUTH, Orientation::WEST
};

template<>
OrientationTraits::valid_values_type OrientationTraits::valid_values = ::valid_values;

void GameState::updateTile(Vector pos, Inventory resources)
{
    if (tiles.size() <= pos.y)
        tiles.resize(pos.y + 1);
    if (tiles.at(pos.y).size() <= pos.x)
        tiles.at(pos.y).resize(pos.x + 1);

    tiles.at(pos.y).at(pos.x) = resources;
}

Inventory GameState::getTileResources(Vector pos) const
{
    return tiles.at(pos.y).at(pos.x);
}

void GameState::addTeam(std::string teamName)
{
    teams.push_back(teamName);
}

void GameState::addPlayer(int id, Vector pos, Orientation orientation, int level, std::string team)
{
    players.try_emplace(id, team, pos, Inventory(), orientation, level);
}

void GameState::updatePlayerPosition(int id, Vector pos, Orientation orientation)
{
    players.at(id).position = pos;
    players.at(id).orientation = orientation;
}

void GameState::updatePlayerLevel(int id, std::uint8_t level)
{
    players.at(id).level = level;
}

void GameState::updatePlayerInventory(int id, Inventory inventory)
{
    players.at(id).inventory = inventory;
}

void GameState::ejectPlayer(int id)
{
}

void GameState::message(std::string message, int id)
{
    this->messages.push_front({id, std::move(message)});
    if (this->messages.size() > 50)
        this->messages.pop_back();
}

void GameState::startIncantation(Vector pos, int level, const std::vector<int>& players)
{

}

void GameState::endIncantation(Vector pos, std::string result)
{
}

void GameState::playerDropsResource(int id, int resourceType)
{
    this->players.at(id).inventory[resourceType]--;
    this->tiles.at(this->players.at(id).position.y).at(this->players.at(id).position.x)[resourceType]++;
}

void GameState::playerCollectsResource(int id, int resourceType)
{
    this->players.at(id).inventory[resourceType]++;
}

void GameState::playerDies(int id)
{
    players.erase(id);
}

void GameState::addEgg(int eggId, int playerId, Vector pos)
{
    eggs.try_emplace(eggId, pos, playerId);
}

void GameState::eggHatches(int eggId)
{
    eggs.erase(eggId);
}

void GameState::eggDies(int eggId)
{
    eggs.erase(eggId);
}

void GameState::setTimeUnit(int timeUnit)
{
    this->_timeUnit = timeUnit;
}

void GameState::endGame(std::string winningTeam)
{
    this->winner = winningTeam;
}
