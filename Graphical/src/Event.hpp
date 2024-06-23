/*
** EPITECH PROJECT, 2024
** Zappy GUI
** File description:
** Zappy::GUI::Event
*/

#ifndef ZAPPY_EVENT_HPP_
    #define ZAPPY_EVENT_HPP_

    #include <algorithm>
    #include <cctype>
    #include <functional>
    #include <sstream>

    #include "utils/enum_traits.hpp"
    #include "utils/extract.hpp"

    #include "GameState.hpp"

namespace Zappy::GUI {
    #include "utils/bits/operators.hpp"

    class Event {
        public:
            enum class Type {
                UNKNOWN,
                MAP_SIZE,
                TEAM_NAME,
                TILE_CONTENT,
                PLAYER_NEW,
                PLAYER_POSITION, PLAYER_LEVEL, PLAYER_INVENTORY,
                PLAYER_EJECTED,
                PLAYER_BROADCAST,
                PLAYER_INCANTATION_START, PLAYER_INCANTATION_END,
                PLAYER_DROP, PLAYER_COLLECT,
                PLAYER_DEATH,
                PLAYER_LAY, EGG_LAID,
                EGG_HATCH, EGG_DIE,
                GAME_END,
                FREQUENCY_GET, FREQUENCY_SET,
                SERVER_MESSAGE,
                COMMAND_UNKNOWN, COMMAND_INVALID
            };
            using Traits = utils::enum_traits<Event::Type>;
            struct Id { int &id; };
            using ParsersMap = std::unordered_map<const Type, const std::function<void(std::istream &is, Event &)>>;
            using UpdatersMap = std::unordered_map<const Event::Type, const std::function<void(const Event &is, GameState &)>>;

            static const ParsersMap Parsers;
            static const UpdatersMap Updaters;

            Type type;

            void update(GameState &gameState) const;

        private:
            int _id, _number;
            Vector _vector;
            Orientation _orientation;
            Inventory _inventory;
            std::string _message;
    };

    inline void operator>>(std::istream &is, Event &event)
    {
        utils::extract(is >> Event::Traits::alpha, event.type);
        Event::Parsers.at(event.type)(is, event);
    }

    inline std::istream &operator>>(std::istream &is, Event::Id id)
    {
        char c;
        is >> c;
        if (c != '#' || isspace(is.peek()))
            is.setstate(std::ios_base::failbit);
        is >> id.id;
        return is;
    }
}

#endif /* !ZAPPY_EVENT_HPP_ */
