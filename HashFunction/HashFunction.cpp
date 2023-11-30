#include "api_hasher.h"

int main()
{
	IMPORT_HASH(LoadLibraryA)("user32.dll");
	IMPORT_HASH(MessageBoxW)(NULL, L"test", L"test", NULL);

	return (0);
}
