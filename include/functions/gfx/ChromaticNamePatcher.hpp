#ifndef CHROMATIC_NAME_PATCHER_HPP
#define CHROMATIC_NAME_PATCHER_HPP

#include <sys/types.h>
#include <string_view>

namespace functions::gfx {
    class ChromaticNamePatcher {
    public:
        static void apply(pid_t pid, unsigned long lib_base, std::string_view app_name);
    };
}

#endif
