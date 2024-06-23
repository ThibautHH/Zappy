/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** GameState.cpp
*/

#include "GameState.hpp"

GameState::GameState()
    : width(0), height(0), timeUnit(0), winningTeam(""), serverMsg("") {}

void GameState::setWidth(int w) {
    this->width = w;
    initializeTiles();
}

void GameState::setHeight(int h) {
    this->height = h;
    initializeTiles();
}

void GameState::initializeTiles() {
    if (width > 0 && height > 0) {
        tiles.resize(height, std::vector<std::vector<int>>(width));
    }
}


void GameState::parseServerMessage(const std::string& message) {

}

void GameState::parseTile(const std::string& message) {

}

void GameState::parsePlayer(const std::string& message) {

}

void GameState::parseEgg(const std::string& message) {

}

void GameState::parseMapSize(const std::string& message) {

}

void GameState::parsePlayerPosition(const std::string& message) {

}

void GameState::parseTeam(const std::string& message) {

}

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

void GameState::playerLaysEgg(int id) {

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

void GameState::unknownCommand() {

}

void GameState::commandParameter() {

}
