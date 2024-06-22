/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Protocol.cpp
*/

#include "../include/Protocol.hpp"
#include <sstream>
#include <iostream>

void Protocol::parseServerMessage(GameState& gameState, const std::string& message) {
    std::istringstream stream(message);
    std::string command;
    stream >> command;

    if (command == "msz") {
        int width, height;
        stream >> width >> height;
        gameState.setWidth(width);
        gameState.setHeight(height);
    } else if (command == "bct") {
        int x, y, q0, q1, q2, q3, q4, q5, q6;
        stream >> x >> y >> q0 >> q1 >> q2 >> q3 >> q4 >> q5 >> q6;
        gameState.updateTile(x, y, {q0, q1, q2, q3, q4, q5, q6});
    } else if (command == "tna") {
        std::string teamName;
        while (stream >> teamName) {
            gameState.addTeam(teamName);
        }
    } else if (command == "pnw") {
        int n, x, y, o, l;
        std::string name;
        stream >> n >> x >> y >> o >> l >> name;
        gameState.addPlayer(n, x, y, o, l, name);
    } else if (command == "ppo") {
        int n, x, y, o;
        stream >> n >> x >> y >> o;
        gameState.updatePlayerPosition(n, x, y, o);
    } else if (command == "plv") {
        int n, l;
        stream >> n >> l;
        gameState.updatePlayerLevel(n, l);
    } else if (command == "pin") {
        int n, x, y, q0, q1, q2, q3, q4, q5, q6;
        stream >> n >> x >> y >> q0 >> q1 >> q2 >> q3 >> q4 >> q5 >> q6;
        gameState.updatePlayerInventory(n, {q0, q1, q2, q3, q4, q5, q6});
    } else if (command == "pex") {
        int n;
        stream >> n;
        gameState.ejectPlayer(n);
    } else if (command == "pbc") {
        int n;
        std::string msg;
        stream >> n >> std::ws;
        std::getline(stream, msg);
        gameState.broadcastMessage(n, msg);
    } else if (command == "pic") {
        int x, y, l;
        std::vector<int> players;
        stream >> x >> y >> l;
        int player;
        while (stream >> player) {
            players.push_back(player);
        }
        gameState.startIncantation(x, y, l, players);
    } else if (command == "pie") {
        int x, y;
        std::string result;
        stream >> x >> y >> result;
        gameState.endIncantation(x, y, result);
    } else if (command == "pfk") {
        int n;
        stream >> n;
        gameState.playerLaysEgg(n);
    } else if (command == "pdr") {
        int n, i;
        stream >> n >> i;
        gameState.playerDropsResource(n, i);
    } else if (command == "pgt") {
        int n, i;
        stream >> n >> i;
        gameState.playerCollectsResource(n, i);
    } else if (command == "pdi") {
        int n;
        stream >> n;
        gameState.playerDies(n);
    } else if (command == "enw") {
        int e, n, x, y;
        stream >> e >> n >> x >> y;
        gameState.addEgg(e, n, x, y);
    } else if (command == "ebo") {
        int e;
        stream >> e;
        gameState.eggHatches(e);
    } else if (command == "edi") {
        int e;
        stream >> e;
        gameState.eggDies(e);
    } else if (command == "sgt") {
        int t;
        stream >> t;
        gameState.setTimeUnit(t);
    } else if (command == "sst") {
        int t;
        stream >> t;
        gameState.setTimeUnit(t);
    } else if (command == "seg") {
        std::string teamName;
        stream >> teamName;
        gameState.endGame(teamName);
    } else if (command == "smg") {
        std::string msg;
        stream >> std::ws;
        std::getline(stream, msg);
        gameState.serverMessage(msg);
    } else if (command == "suc") {
        gameState.unknownCommand();
    } else if (command == "sbp") {
        gameState.commandParameter();
    }
}
