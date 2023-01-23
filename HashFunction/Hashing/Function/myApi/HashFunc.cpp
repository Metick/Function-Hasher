#include "../../../global.h"
#include "HashFunc.h"
#include "Table.hpp"

namespace API {

	void(__stdcall* temp_Test)() = nullptr;

	void hash_Test() {
		std::string func = "Test";
		const auto _hash = t1ha0(func.c_str(), func.size(), STRONG_SEED);
		temp_Test = static_cast<void(__stdcall*)()>(Hashing::Table::get(_hash, func.size(), STRONG_SEED));

		return temp_Test();
	}		
}