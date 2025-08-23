#define _GNU_SOURCE
#include "utils/Memory.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/syscall.h>

namespace utils {

bool Memory::write_memory(pid_t pid, void *remote_addr, void *local_addr, size_t size) {
    // yea working /proc/pid/mem 
    std::string mem_path = "/proc/" + std::to_string(pid) + "/mem";
    int mem_fd = open(mem_path.c_str(), O_RDWR);
    if (mem_fd == -1) {
        std::cerr << "Failed to open " << mem_path << std::endl;
        return false;
    }

    if (lseek(mem_fd, reinterpret_cast<off_t>(remote_addr), SEEK_SET) == -1) {
        std::cerr << "Failed to seek to address" << std::endl;
        close(mem_fd);
        return false;
    }

    ssize_t result = write(mem_fd, local_addr, size);
    close(mem_fd);

    if (result != static_cast<ssize_t>(size)) {
        std::cerr << "Write failed. Expected " << size << " bytes, wrote " << result << std::endl;
    }

    return (result == static_cast<ssize_t>(size));
}

pid_t Memory::find_pid(std::string_view process_name) {
    std::string command = "pidof ";
    command += process_name;
    
    FILE *fp = popen(command.c_str(), "r");
    if (!fp) return -1;
    
    pid_t pid = -1;
    char buffer[20];
    if (fgets(buffer, sizeof(buffer), fp) != nullptr) {
        try {
            pid = std::stoi(buffer);
        } catch (...) {
            pid = -1;
        }
    }
    pclose(fp);
    return pid;
}

unsigned long Memory::find_lib_base(pid_t pid, std::string_view lib_name) {
    std::string path = "/proc/" + std::to_string(pid) + "/maps";
    std::ifstream maps_file(path);
    if (!maps_file.is_open()) return 0;

    std::string line;
    unsigned long base = 0;

    while (std::getline(maps_file, line)) {
        if (line.find(lib_name) != std::string::npos && line.find("r-xp") != std::string::npos) {
            std::stringstream ss(line);
            ss >> std::hex >> base;
            break;
        }
    }
    maps_file.close();
    return base;
}

}
