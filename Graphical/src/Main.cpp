/*
** EPITECH PROJECT, 2024
** Zappy GUI
** File description:
** Program entrypoint
*/

#include <format>
#include <iostream>
#include <string_view>

#include "Game.hpp"

static void print_usage(std::ostream &os, const char * const program_name)
{
    os << std::format("USAGE: {} -p port -h machine", program_name) << std::endl;
}

int main(const int argc, const char * const * const argv)
{
    if (argc == 2 && std::string_view(argv[1]) == "-help") {
        print_usage(std::cout, argv[0]);
        return 0;
    }
    if (argc != 5
        || std::string_view(argv[1]) != "-p"
        || std::string_view(argv[3]) != "-h") {
        print_usage(std::cerr, argv[0]);
        return 84;
    }

    Zappy::GUI::Game(Zappy::GUI::NetworkClient(argv[4], argv[2])).run();

    return 0;
}
