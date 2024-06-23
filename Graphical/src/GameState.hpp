/*
** EPITECH PROJECT, 2024
** Zappy GUI
** File description:
** Zappy::GUI::GameState
*/

#ifndef ZAPPY_GUI_GAMESTATE_HPP_
    #define ZAPPY_GUI_GAMESTATE_HPP_

    #include <cstdint>
    #include <istream>
    #include <string>
    #include <vector>
    #include <unordered_map>

namespace Zappy::GUI {
    enum class Orientation {
        NORTH = 1,
        EAST,
        SOUTH,
        WEST
    };

    struct Vector {
        int x, y;
    };

    inline std::istream &operator>>(std::istream& is, Vector& vec)
    {
        return is >> vec.x >> vec.y;
    }

    struct Inventory {
        std::uint16_t food, linemate, deraumere, sibur, mendiane, phiras, thystame;

        inline std::uint16_t &operator[](int index)
        {
            switch (index) {
                case 0: return this->food;
                case 1: return this->linemate;
                case 2: return this->deraumere;
                case 3: return this->sibur;
                case 4: return this->mendiane;
                case 5: return this->phiras;
                case 6: return this->thystame;
                default: throw std::out_of_range("Invalid resource index");
            }
        }
    };

    inline std::istream &operator>>(std::istream& is, Inventory& inv)
    {
        return is >> inv.food >> inv.linemate >> inv.deraumere >> inv.sibur
            >> inv.mendiane >> inv.phiras >> inv.thystame;
    }

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
            void setWidth(int w) { this->width = w; }
            void setHeight(int h) { this->height = h; }
            int getWidth() const { return width; }
            int getHeight() const { return height; }

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

            const std::vector<std::vector<std::vector<int>>>& getTiles() const { return tiles; }
            const std::unordered_map<int, Player>& getPlayers() const { return players; }
            const std::unordered_map<int, Egg>& getEggs() const { return eggs; }

        private:
            int width, height;
            int timeUnit;
            std::string winningTeam;
            std::string serverMsg;

            std::vector<std::string> teams;
            std::unordered_map<int, Player> players;
            std::unordered_map<int, Egg> eggs;
            std::vector<std::vector<std::vector<int>>> tiles;
    };
}

#endif /* !ZAPPY_GUI_GAMESTATE_HPP_ */
