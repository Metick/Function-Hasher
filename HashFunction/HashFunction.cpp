#include "global.h"
#include "Hashing/Function/myApi/HashFunc.h"
#include "Hashing/Function/winApi/hashWork.hpp"

int main() {
	printf("Calling test after 1 second\n");

	hash_Sleep(1000);

	API::hash_Test();
}


