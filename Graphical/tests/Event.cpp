/*
** EPITECH PROJECT, 2024
** Zappy GUI
** File description:
** Zappy::GUI::Event tests
*/

#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <ostream>

#include "../src/Event.hpp"

using namespace Zappy::GUI;

template<>
Event::Traits::to_string_type Event::Traits::to_string = {
    { Event::Type::MAP_SIZE, "Map size" },
    { Event::Type::TEAM_NAME, "Team name" },
    { Event::Type::TILE_CONTENT, "Tile content" },
    { Event::Type::PLAYER_NEW, "New player" },
    { Event::Type::PLAYER_POSITION, "Player position" },
    { Event::Type::PLAYER_LEVEL, "Player level" },
    { Event::Type::PLAYER_INVENTORY, "Player inventory" },
    { Event::Type::PLAYER_EJECTED, "Player eject" },
    { Event::Type::PLAYER_BROADCAST, "Player broadcast" },
    { Event::Type::PLAYER_INCANTATION_START, "Incantation start" },
    { Event::Type::PLAYER_INCANTATION_END, "Incantation end" },
    { Event::Type::PLAYER_DROP, "Player drop" },
    { Event::Type::PLAYER_COLLECT, "Player collection" },
    { Event::Type::PLAYER_DEATH, "Player death" },
    { Event::Type::PLAYER_LAY, "Player snu-snu" },
    { Event::Type::EGG_LAID, "Egg laid" },
    { Event::Type::EGG_HATCH, "Egg hatched" },
    { Event::Type::EGG_DIE, "Egg smashed" },
    { Event::Type::GAME_END, "Game end" },
    { Event::Type::FREQUENCY_GET, "Get frequency" },
    { Event::Type::FREQUENCY_SET, "Set frequency" },
    { Event::Type::SERVER_MESSAGE, "Server message" },
    { Event::Type::COMMAND_UNKNOWN, "Unknown client command" },
    { Event::Type::COMMAND_INVALID, "Invalid client command parameter" }
};

using OrientationTraits = utils::enum_traits<Orientation>;

template<>
OrientationTraits::to_string_type OrientationTraits::to_string = {
    {Orientation::NORTH, "North"},
    {Orientation::EAST, "East"},
    {Orientation::SOUTH, "South"},
    {Orientation::WEST, "West"}
};

namespace Zappy::GUI {
    constexpr bool operator==(const Vector lhs, const Vector rhs) noexcept
    {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    constexpr bool operator==(const Inventory lhs, const Inventory rhs) noexcept
    {
        return lhs.food == rhs.food && lhs.linemate == rhs.linemate && lhs.deraumere == rhs.deraumere
            && lhs.sibur == rhs.sibur && lhs.mendiane == rhs.mendiane && lhs.phiras == rhs.phiras
            && lhs.thystame == rhs.thystame;
    }

    inline std::ostream &operator<<(std::ostream& os, const Vector vec)
    {
        return os << '(' << vec.x << ':' << vec.y << ')';
    }

    inline std::ostream &operator<<(std::ostream& os, const Inventory vec)
    {
        return os << "[food: " << vec.food << "; linemate: " << vec.linemate << "; deraumere: "
            << vec.deraumere << "; sibur: " << vec.sibur << "; mendiane: " << vec.mendiane
            << "; phiras: " << vec.phiras << "; thystame: " << vec.thystame << ']';
    }
}

Test(Event, constructor)
{
    Event event;

    cr_expect(eq(event.type, Event::Type::UNKNOWN));
}

Test(Event, map_size)
{
    Event event;

    cr_expect(not(bool((std::istringstream("msz 10 10") >> event).fail())));
    cr_expect(eq(event.type, Event::Type::MAP_SIZE));
    cr_expect(eq(event.vector, Vector(10, 10)));
}

Test(Event, team_name)
{
    Event event;

    cr_expect(not(bool((std::istringstream("tna Team1") >> event).fail())));
    cr_expect(eq(event.type, Event::Type::TEAM_NAME));
    cr_expect(eq(event.message, "Team1"));
}

Test(Event, tile_content)
{
    Event event;

    cr_expect(not(bool((std::istringstream("bct 1 42 4 3 5 6 7 9 0") >> event).fail())));
    cr_expect(eq(event.type, Event::Type::TILE_CONTENT));
    cr_expect(eq(event.vector, Vector(1, 42)));
    cr_expect(eq(type(Inventory), event.inventory, (Inventory{4, 3, 5, 6, 7, 9, 0})));
}

Test(Event, player_new)
{
    Event event;

    cr_expect(not(bool((std::istringstream("pnw #1 10 10 3 1 Team1") >> event).fail())));
    cr_expect(eq(event.type, Event::Type::PLAYER_NEW));
    cr_expect(eq(event.id, 1));
    cr_expect(eq(event.vector, Vector(10, 10)));
    cr_expect(eq(event.orientation, Orientation::SOUTH));
    cr_expect(eq(event.number, 1));
    cr_expect(eq(event.message, "Team1"));
}

Test(Event, player_position)
{
    Event event;

    cr_expect(not(bool((std::istringstream("ppo #1 10 10 3") >> event).fail())));
    cr_expect(eq(event.type, Event::Type::PLAYER_POSITION));
    cr_expect(eq(event.id, 1));
    cr_expect(eq(event.vector, Vector(10, 10)));
    cr_expect(eq(event.orientation, Orientation::SOUTH));
}

Test(Event, player_level)
{
    Event event;

    cr_expect(not(bool((std::istringstream("plv #1 3") >> event).fail())));
    cr_expect(eq(event.type, Event::Type::PLAYER_LEVEL));
    cr_expect(eq(event.id, 1));
    cr_expect(eq(event.number, 3));
}

Test(Event, player_inventory)
{
    Event event;

    cr_expect(not(bool((std::istringstream("pin #1 4 3 5 6 7 9 0") >> event).fail())));
    cr_expect(eq(event.type, Event::Type::PLAYER_INVENTORY));
    cr_expect(eq(event.id, 1));
    cr_expect(eq(type(Inventory), event.inventory, (Inventory{4, 3, 5, 6, 7, 9, 0})));
}

Test(Event, player_ejected)
{
    Event event;

    cr_expect(not(bool((std::istringstream("pex #1") >> event).fail())));
    cr_expect(eq(event.type, Event::Type::PLAYER_EJECTED));
    cr_expect(eq(event.id, 1));
}

Test(Event, player_broadcast)
{
    Event event;

    cr_expect(not(bool((std::istringstream("pbc #1 Hello World!") >> event).fail())));
    cr_expect(eq(event.type, Event::Type::PLAYER_BROADCAST));
    cr_expect(eq(event.id, 1));
    cr_expect(eq(event.message, "Hello World!"));
}

Test(Event, player_incantation_start)
{
    Event event;

    cr_expect(not(bool((std::istringstream("pic 10 10 3 #1") >> event).fail())));
    cr_expect(eq(event.type, Event::Type::PLAYER_INCANTATION_START));
    cr_expect(eq(event.vector, Vector(10, 10)));
    cr_expect(eq(event.number, 3));
    cr_expect(eq(event.id, 1));
}

Test(Event, player_incantation_end)
{
    Event event;

    cr_expect(not(bool((std::istringstream("pie 10 10 ok") >> event).fail())));
    cr_expect(eq(event.type, Event::Type::PLAYER_INCANTATION_END));
    cr_expect(eq(event.vector, Vector(10, 10)));
    cr_expect(eq(event.message, "ok"));
}

Test(Event, player_drop)
{
    Event event;

    cr_expect(not(bool((std::istringstream("pdr #14 3") >> event).fail())));
    cr_expect(eq(event.type, Event::Type::PLAYER_DROP));
    cr_expect(eq(event.id, 14));
    cr_expect(eq(event.number, 3));
}

Test(Event, player_collect)
{
    Event event;

    cr_expect(not(bool((std::istringstream("pgt #61 3") >> event).fail())));
    cr_expect(eq(event.type, Event::Type::PLAYER_COLLECT));
    cr_expect(eq(event.id, 61));
    cr_expect(eq(event.number, 3));
}

Test(Event, player_death)
{
    Event event;

    std::istringstream("pdi #1") >> event;
    cr_expect(eq(event.type, Event::Type::PLAYER_DEATH));
    cr_expect(eq(event.id, 1));
}

Test(Event, player_lay)
{
    Event event;

    std::istringstream("pfk #1") >> event;
    cr_expect(eq(event.type, Event::Type::PLAYER_LAY));
    cr_expect(eq(event.id, 1));
}

Test(Event, egg_laid)
{
    Event event;

    std::istringstream("enw #1 #10 10 10") >> event;
    cr_expect(eq(event.type, Event::Type::EGG_LAID));
    cr_expect(eq(event.id, 1));
    cr_expect(eq(event.number, 10));
    cr_expect(eq(event.vector, Vector(10, 10)));
}

Test(Event, egg_hatch)
{
    Event event;

    cr_expect(not(bool((std::istringstream("ebo #1") >> event).fail())));
    cr_expect(eq(event.type, Event::Type::EGG_HATCH));
    cr_expect(eq(event.id, 1));
}

Test(Event, egg_die)
{
    Event event;

    cr_expect(not(bool((std::istringstream("edi #1") >> event).fail())));
    cr_expect(eq(event.type, Event::Type::EGG_DIE));
    cr_expect(eq(event.id, 1));
}

Test(Event, game_end)
{
    Event event;

    cr_expect(not(bool((std::istringstream("seg Team1") >> event).fail())));
    cr_expect(eq(event.type, Event::Type::GAME_END));
    cr_expect(eq(event.message, "Team1"));
}

Test(Event, frequency_get)
{
    Event event;

    cr_expect(not(bool((std::istringstream("sgt 100") >> event).fail())));
    cr_expect(eq(event.type, Event::Type::FREQUENCY_GET));
    cr_expect(eq(event.number, 100));
}

Test(Event, frequency_set)
{
    Event event;

    cr_expect(not(bool((std::istringstream("sst 100") >> event).fail())));
    cr_expect(eq(event.type, Event::Type::FREQUENCY_SET));
    cr_expect(eq(event.number, 100));
}

Test(Event, server_message)
{
    Event event;

    cr_expect(not(bool((std::istringstream("smg Hello World!") >> event).fail())));
    cr_expect(eq(event.type, Event::Type::SERVER_MESSAGE));
    cr_expect(eq(event.message, "Hello World!"));
}

Test(Event, command_unknown)
{
    Event event;

    cr_expect(not(bool((std::istringstream("suc") >> event).fail())));
    cr_expect(eq(event.type, Event::Type::COMMAND_UNKNOWN));
}

Test(Event, command_invalid)
{
    Event event;

    cr_expect(not(bool((std::istringstream("sbp") >> event).fail())));
    cr_expect(eq(event.type, Event::Type::COMMAND_INVALID));
}
