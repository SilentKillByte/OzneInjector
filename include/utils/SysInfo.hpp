#ifndef SYSINFO_HPP
#define SYSINFO_HPP

#include <string>

namespace utils {
    class SysInfo {
    public:
        static std::string get_device_model();
    };
}

#endif
