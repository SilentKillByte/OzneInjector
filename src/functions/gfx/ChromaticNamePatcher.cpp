#include "functions/gfx/ChromaticNamePatcher.hpp"
#include "utils/Memory.hpp"
#include "utils/SysInfo.hpp"
#include <iostream>
#include <cstdint>
#include <vector>

namespace functions::gfx {

constexpr unsigned long TARGET_OFFSET = 0x99B158; // LogicDailyData__isBrawlPassPremiumUnlocked 

/*
.text:000000000099B158                 ADD             X8, X0, #0x1B8
.text:000000000099B15C                 LDR             W8, [X8,#0xC]

MOV W0, #1; RET;
*/

void ChromaticNamePatcher::apply(pid_t pid, unsigned long lib_base, std::string_view app_name) {
    void* target_addr = reinterpret_cast<void*>(lib_base + TARGET_OFFSET);
    std::vector<uint32_t> patch_bytes = { 0x52800020, 0xD65F03C0 };

    std::string device_model = utils::SysInfo::get_device_model();

    // memory process apply pactch
    if (utils::Memory::write_memory(pid, target_addr, patch_bytes.data(), patch_bytes.size() * sizeof(uint32_t))) {
        std::cout << "[+] chromatic name active" << std::endl;
    } else {
        std::cout << "[-] chromatic name failed" << std::endl;
    }
}

}
