#pragma once

#include <Windows.h>
#include <string>
#include <unordered_map>
#include <codecvt>
#include <random>
#include <winternl.h>

#include "Tools/Utils.h"
#include "Tools/crt.h"

#include "Hashing/t1ha/t1ha.h"

#define STRONG_SEED 10376313370251892926
#define RAND_DWORD1		 0x03EC7B5E 
#define ROR(x,n) (((x) >> (n)) | ((x) << (32-(n))))