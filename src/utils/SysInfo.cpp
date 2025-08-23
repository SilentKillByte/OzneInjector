#include "utils/SysInfo.hpp"
#include <cstdio>
#include <array>
#include <string>

namespace utils {

std::string SysInfo::get_device_model() {
    std::array<char, 128> buffer;
    std::string result = "UnknownDevice";
    FILE* pipe = popen("getprop ro.product.model", "r");
    if (!pipe) return result;

    if (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result = buffer.data();

        result.erase(result.find_last_not_of("\n\r") + 1);
    }
    pclose(pipe);
    return result;
}

}
