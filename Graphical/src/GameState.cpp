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

void GameState::updateTile(int x, int y, const std::vector<int>& resources) {
    if (y >= 0 && y < tiles.size() && x >= 0 && x < tiles[y].size()) {
        tiles[y][x] = resources;
    }
}

const std::vector<int>& GameState::getTileResources(int x, int y) const {
    if (y >= 0 && y < tiles.size() && x >= 0 && x < tiles[y].size()) {
        return tiles[y][x];
    }
    static const std::vector<int> empty; // Retourner un vecteur vide en cas d'indice invalide
    return empty;
}

void GameState::addTeam(const std::string& teamName) {
    teams.push_back(teamName);
}

void GameState::addPlayer(int id, int x, int y, int orientation, int level, const std::string& team) {
    players[id] = {x, y, orientation, level, team, {}};
}

void GameState::updatePlayerPosition(int id, int x, int y, int orientation) {
    auto& player = players[id];
    player.x = x;
    player.y = y;
    player.orientation = orientation;
}

void GameState::updatePlayerLevel(int id, int level) {
    players[id].level = level;
}

void GameState::updatePlayerInventory(int id, const std::vector<int>& inventory) {
    players[id].inventory = inventory;
}

void GameState::ejectPlayer(int id) {

}

void GameState::broadcastMessage(int id, const std::string& message) {

}

void GameState::startIncantation(int x, int y, int level, const std::vector<int>& players) {

}

void GameState::endIncantation(int x, int y, const std::string& result) {
}

void GameState::playerDropsResource(int id, int resourceType) {
}

void GameState::playerCollectsResource(int id, int resourceType) {

}

void GameState::playerDies(int id) {
    players.erase(id);
}

void GameState::addEgg(int eggId, int playerId, int x, int y) {
    eggs[eggId] = {playerId, x, y, false};
}

void GameState::eggHatches(int eggId) {
    eggs[eggId].hatched = true;
}

void GameState::eggDies(int eggId) {
    eggs.erase(eggId);
}

void GameState::setTimeUnit(int timeUnit) {
    this->timeUnit = timeUnit;
}

void GameState::endGame(const std::string& winningTeam) {
    this->winningTeam = winningTeam;
}

void GameState::serverMessage(const std::string& message) {
    this->serverMsg = message;
}
