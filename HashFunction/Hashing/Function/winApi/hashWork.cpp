#include "exportWork.hpp"

void (WINAPI* temp_Sleep)(DWORD dwMilliseconds) = nullptr;

void hash_Sleep(DWORD dwMilliseconds) {
    std::string func = "Sleep";
    const auto _hash = t1ha0(func.c_str(), func.size(), STRONG_SEED);
    temp_Sleep = static_cast<void(WINAPI *)(DWORD)>(getApi(_hash, "kernel32.dll", func.size(), STRONG_SEED));

    return temp_Sleep(dwMilliseconds);
}