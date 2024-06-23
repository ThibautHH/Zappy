/*
** EPITECH PROJECT, 2024
** Zappy GUI
** File description:
** Termination
*/

#ifndef TERMINATION_HPP_
    #define TERMINATION_HPP_

    #include <exception>

/**
 * @brief Class responsible for handling termination of the program
 */
class Termination {
    private:
        static constexpr const char ProgramName[] = "Zappy GUI";
        static const std::terminate_handler DefaultTerminateHandler;
        static const int ExitCode = 84;
        static void terminate();
};

#endif /* !TERMINATION_HPP_ */
