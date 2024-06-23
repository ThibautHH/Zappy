/*
** EPITECH PROJECT, 2024
** Zappy GUI
** File description:
** Termination
*/

#include <cxxabi.h>
#include <iostream>
#include <memory>

#include "Termination.hpp"

const std::terminate_handler Termination::DefaultTerminateHandler = std::set_terminate(Termination::terminate);

void Termination::terminate()
{
    std::exception_ptr eptr = std::current_exception();
    if (eptr)
        try {
            std::rethrow_exception(eptr);
        } catch (const std::exception &e) {
            const char * const rawName = typeid(e).name();
            int status;
            const std::unique_ptr<char, decltype(std::free) *> name(
                abi::__cxa_demangle(rawName, nullptr, nullptr, &status),
                std::free);
            std::cerr << ProgramName << " terminated after throwing an instance of '" << (name ? name.get() : rawName)
                << "'\n  what(): " << e.what() << std::endl;
        } catch (...) {
            (*DefaultTerminateHandler)();
        }
    std::exit(ExitCode);
}
