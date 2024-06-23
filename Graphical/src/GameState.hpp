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
    #include <list>
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
        std::string team;
        Vector position;
        Inventory inventory;
        Orientation orientation;
        std::uint8_t level;
    };

    struct Egg {
        Vector position;
        int playerId;
    };

    class GameState {
        public:
            using Message = std::tuple<int, std::string>;
            void setSize(Vector size) { this->_size = size; }
            Vector getSize() const { return _size; }

            void updateTile(Vector pos, Inventory resources);
            Inventory getTileResources(Vector pos) const;
            void addTeam(std::string teamName);
            void addPlayer(int id, Vector pos, Orientation orientation, int level, std::string team);
            void updatePlayerPosition(int id, Vector pos, Orientation orientation);
            void updatePlayerLevel(int id, std::uint8_t level);
            void updatePlayerInventory(int id, Inventory inventory);
            void ejectPlayer(int id);
            void message(std::string message, int id = -1);
            void startIncantation(Vector pos, int level, const std::vector<int>& players);
            void endIncantation(Vector pos, std::string result);
            void playerDropsResource(int id, int resourceType);
            void playerCollectsResource(int id, int resourceType);
            void playerDies(int id);
            void addEgg(int eggId, int playerId, Vector pos);
            void eggHatches(int eggId);
            void eggDies(int eggId);
            void setTimeUnit(int timeUnit);
            void endGame(std::string winningTeam);

            const std::vector<std::vector<Inventory>>& getTiles() const { return tiles; }
            const std::unordered_map<int, Player>& getPlayers() const { return players; }
            const std::unordered_map<int, Egg>& getEggs() const { return eggs; }

        private:
            Vector _size;
            int _timeUnit;
            std::string _winningTeam;

            std::vector<std::string> teams;
            std::vector<std::vector<Inventory>> tiles;
            std::unordered_map<int, Player> players;
            std::unordered_map<int, Egg> eggs;
            std::list<Message> messages;
    };
}

#endif /* !ZAPPY_GUI_GAMESTATE_HPP_ */
