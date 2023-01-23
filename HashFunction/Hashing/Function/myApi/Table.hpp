#pragma once

#include "../../global.h"

namespace Hashing {
	namespace Table {

		struct Function {
			void* ptr;
			std::string name;
			//...
		};

		struct FunctionHeader {
			Function function;
			//...
		};

		void test() {
			printf("Hello World!\n");
		}

		//Vector of functions, probably would be faster as a unordered_map?
		std::vector<FunctionHeader> g_functions = {
			{{&test, "Test"}}

		};

		__forceinline LPVOID parseFunctionTable(uint64_t api_hash, uint64_t len, const uint64_t seed) {
		
			if (!g_functions.empty()) {
				for (auto& function : g_functions) {
					const uint64_t get_hash = t1ha0(function.function.name.c_str(), len, seed);
					if (api_hash == get_hash) {
						//todo: check if we can make a ordinal, return ordinal & then have the addr random allocated somewhere which can be found using ordinal to some array

						return function.function.ptr;
					}
				}
			}
			return NULL;
		}

		__forceinline LPVOID get(uint64_t api_hash, uint64_t len, const uint64_t seed) {
			//x64 only
			const auto ModuleList = 0x18;
			const auto ModuleListFlink = 0x18;
			const auto KernelBaseAddr = 0x10;
			const intptr_t peb = __readgsqword(0x60);

			const auto mdllist = *(intptr_t*)(peb + ModuleList);
			const auto mlink = *(intptr_t*)(mdllist + ModuleListFlink);
			auto mdl = (LDR_MODULE*)mlink;

			do {
				mdl = (LDR_MODULE*)mdl->e[0].Flink;
				if (mdl->base != nullptr) {
					if (Tools::CRT::String::myStrStr((char*)Tools::CRT::String::ws2s(mdl->dllname.Buffer).c_str(), (char*)".exe") != NULL) {
						break;
					}
				}
			} while (mlink != (intptr_t)mdl);

			HMODULE baseAddr = static_cast<HMODULE>(mdl->base);
			//this above, is honestly just there to confuse right now, it's planned for a future thing but haven't figured out how to do that yet, if even possible.

			return static_cast<LPVOID>(parseFunctionTable(api_hash, len, seed));
		}
	}
}