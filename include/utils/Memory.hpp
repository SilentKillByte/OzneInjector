#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <string_view>
#include <cstddef>
#include <sys/types.h>

namespace utils {
    class Memory {
    public:
        static bool write_memory(pid_t pid, void* remote_addr, void* local_addr, size_t size);
        static pid_t find_pid(std::string_view process_name);
        static unsigned long find_lib_base(pid_t pid, std::string_view lib_name);
    };
}

#endif
