#include "utils/Memory.hpp"
#include "functions/gfx/ChromaticNamePatcher.hpp"
#include <iostream>
#include <unistd.h>

extern "C" {
    __attribute__((visibility("default")))
    int inject(const char *pkg_name, const char *lib_name, const char *app_name) {
        std::cout << "    / _  |   Ozne 1.2 - toolkit\n"
                  << "   | (_| |\n"
                  << "    > _  |   Commands:\n"
                  << "   /_/ |_|     exit/quit -> Exit\n"

                  << "   . . . .    more information with @hwhsysiaka\n"
                  << "   . . . .\n" << std::flush;

        pid_t target_pid = utils::Memory::find_pid(pkg_name);
        if (target_pid == -1) {
            std::cerr << "Process `" << pkg_name << "` not found" << std::endl;
            return 1;
        }

        std::cout << "Process `" << pkg_name << "` found with PID: " << target_pid << std::endl;

        unsigned long base = utils::Memory::find_lib_base(target_pid, lib_name);
        if (!base) {
            std::cerr << "Library not found: " << lib_name << std::endl;
            return 1;
        }

        // apply patch chromatic
        functions::gfx::ChromaticNamePatcher::apply(target_pid, base, app_name);

        while (true) {
            sleep(1);
        }

        return 0;
    }
}
