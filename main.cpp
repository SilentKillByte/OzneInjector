#include "config/Config.hpp"
#include <iostream>
#include <dlfcn.h>

typedef int (*inject_func)(const char*, const char*, const char*);

int main() {
    void *handle = dlopen("./libpornozne.so", RTLD_LAZY);
    if (!handle) {
        std::cerr << "Error loading library: " << dlerror() << std::endl;
        return 1;
    }

    auto inject = reinterpret_cast<inject_func>(dlsym(handle, "inject"));
    if (!inject) {
        std::cerr << "Error finding symbol: " << dlerror() << std::endl;
        dlclose(handle);
        return 1;
    }

    // called functiosn inject with parameters config
    int result = inject(config::TARGET_PACKAGE_NAME.data(),
                        config::TARGET_LIBRARY_NAME.data(),
                        config::TARGET_APP_NAME.data());

    dlclose(handle);
    return result;
}
