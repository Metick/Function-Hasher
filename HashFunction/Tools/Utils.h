#pragma once

struct LDR_MODULE
{
    LIST_ENTRY e[3];
    HMODULE base;
    void* entry;
    UINT size;
    UNICODE_STRING dllPath;
    UNICODE_STRING dllname;
};

namespace Tools {
	namespace Utils {
		extern __forceinline HMODULE getModule(std::string module);
	}
}