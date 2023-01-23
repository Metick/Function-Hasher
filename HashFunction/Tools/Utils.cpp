#include "../global.h"
#include "Utils.h"
#include "crt.h"

namespace Tools {
	namespace Utils {
        __forceinline HMODULE getModule(std::string module) {
            const auto ModuleList = 0x18;
            const auto ModuleListFlink = 0x18;
            const INT_PTR peb = __readgsqword(0x60);
            const auto mdllist = *(INT_PTR*)(peb + ModuleList);
            const auto mlink = *(INT_PTR*)(mdllist + ModuleListFlink);
            auto mdl = (LDR_MODULE*)mlink;

            do {
                mdl = (LDR_MODULE*)mdl->e[0].Flink;
                if (mdl->base != nullptr) {
                    auto bffr = CRT::String::ws2s(mdl->dllname.Buffer);

                    std::transform(bffr.begin(), bffr.end(), bffr.begin(), [](unsigned char c) { return std::tolower(c); });

                    if (CRT::String::myStrStr((char*)bffr.c_str(), (char*)module.c_str()) != NULL) {
                        return mdl->base;
                        break;
                    }
                }
            } while (mlink != (INT_PTR)mdl);

            return 0;
        }
	}
}