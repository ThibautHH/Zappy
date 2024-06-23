/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** GameState.hpp
*/

#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <string>
#include <vector>
#include <map>

struct Player {
    int x, y, orientation, level;
    std::string team;
    std::vector<int> inventory;
};

struct Egg {
    int playerId, x, y;
    bool hatched;
};

class GameState {
public:
    GameState();
    void setWidth(int w);
    void setHeight(int h);
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    void initializeTiles();
    void updateTile(int x, int y, const std::vector<int>& resources);
    const std::vector<int>& getTileResources(int x, int y) const;
    void addTeam(const std::string& teamName);
    void addPlayer(int id, int x, int y, int orientation, int level, const std::string& team);
    void updatePlayerPosition(int id, int x, int y, int orientation);
    void updatePlayerLevel(int id, int level);
    void updatePlayerInventory(int id, const std::vector<int>& inventory);
    void ejectPlayer(int id);
    void broadcastMessage(int id, const std::string& message);
    void startIncantation(int x, int y, int level, const std::vector<int>& players);
    void endIncantation(int x, int y, const std::string& result);
    void playerLaysEgg(int id);
    void playerDropsResource(int id, int resourceType);
    void playerCollectsResource(int id, int resourceType);
    void playerDies(int id);
    void addEgg(int eggId, int playerId, int x, int y);
    void eggHatches(int eggId);
    void eggDies(int eggId);
    void setTimeUnit(int timeUnit);
    void endGame(const std::string& winningTeam);
    void serverMessage(const std::string& message);
    void unknownCommand();
    void commandParameter();

    void parseServerMessage(const std::string& message);
    void parseTile(const std::string& message);
    void parsePlayer(const std::string& message);
    void parseEgg(const std::string& message);
    void parseMapSize(const std::string& message);
    void parsePlayerPosition(const std::string& message);
    void parseTeam(const std::string& message);

    const std::vector<std::vector<std::vector<int>>>& getTiles() const { return tiles; }
    const std::map<int, Player>& getPlayers() const { return players; }
    const std::map<int, Egg>& getEggs() const { return eggs; }

private:
    int width, height;
    int timeUnit;
    std::string winningTeam;
    std::string serverMsg;

    std::vector<std::string> teams;
    std::map<int, Player> players;
    std::map<int, Egg> eggs;
    std::vector<std::vector<std::vector<int>>> tiles;
};

#endif

