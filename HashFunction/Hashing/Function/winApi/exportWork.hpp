#pragma once
#include "../../../global.h"

#include "hashWork.hpp"
#include "exportWork.hpp"

typedef struct _PEB_LDR_DATA_ {
    BYTE Reserved1[8];
    PVOID Reserved2[3];
    LIST_ENTRY *InMemoryOrderModuleList;
} PEB_LDR_DATA_, *PPEB_LDR_DATA_;

typedef struct _PEB_c {
    BYTE Reserved1[2];
    BYTE BeingDebugged;
    BYTE Reserved2[21];
    PPEB_LDR_DATA_ Ldr;
} PEB_c;

#pragma warning (disable : 4996)

__forceinline HMODULE _getKernel32Handle(void) {
    HMODULE dwResult = NULL;
    PEB_c *lpPEB = NULL;
    SIZE_T *lpFirstModule = NULL;

    lpPEB = *(PEB_c **)(__readgsqword(0x30) + 0x60); //get a pointer to the PEB

    // PEB->Ldr->LdrInMemoryOrderModuleList
    // PEB->Ldr = 0x0C
    // Ldr->LdrInMemoryOrderModuleList = 0x14
    lpFirstModule = (SIZE_T *)lpPEB->Ldr->InMemoryOrderModuleList;
    SIZE_T *lpCurrModule = lpFirstModule;
    do {
        PWCHAR szwModuleName = (PWCHAR)lpCurrModule[10]; // 0x28 - module name in unicode
        uint32_t i = 0;
        uint32_t dwHash = 0;
        while (szwModuleName[i]) {
        
            BYTE zByte = (BYTE)szwModuleName[i];
            
            if (zByte >= 'a' && zByte <= 'z')
                zByte -= 0x20; // Uppercase
            
            dwHash = ROR(dwHash, 13) + zByte;
            i++;
        }
        if ((dwHash ^ RAND_DWORD1) == ( 0x6E2BCA17  ^ RAND_DWORD1)) {// KERNEL32.DLL hash
            dwResult = (HMODULE)lpCurrModule[4];
            return dwResult;
        }
        lpCurrModule = (SIZE_T *)lpCurrModule[0]; // next module in linked list
    }
    while (lpFirstModule != (SIZE_T *) lpCurrModule[0]);
    
    return dwResult;
}

static HMODULE (WINAPI *temp_LoadLibraryA)(__in LPCSTR file_name) = nullptr;
static int (*temp_lstrcmpiW)(LPCWSTR lpString1, LPCWSTR lpString2) = nullptr;

__forceinline LPVOID parseExportTable(HMODULE module, uint64_t api_hash, uint64_t len, const uint64_t seed) {
    PIMAGE_DOS_HEADER img_dos_header;
    PIMAGE_NT_HEADERS img_nt_header;
    PIMAGE_EXPORT_DIRECTORY in_export;

    img_dos_header = (PIMAGE_DOS_HEADER)module;
    img_nt_header = (PIMAGE_NT_HEADERS)((uintptr_t)img_dos_header + img_dos_header->e_lfanew);
    in_export = (PIMAGE_EXPORT_DIRECTORY)((uintptr_t)img_dos_header + img_nt_header->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
    
    PDWORD rva_name;
    PWORD rva_ordinal;
    
    rva_name = (PDWORD)((uintptr_t)img_dos_header + in_export->AddressOfNames);
    rva_ordinal = (PWORD)((uintptr_t)img_dos_header + in_export->AddressOfNameOrdinals);
    
    uint64_t ord = -1;
    char *api_name;
    unsigned int i;

    for (i = 0; i < in_export->NumberOfNames - 1; i++) {
        api_name = (PCHAR)((uintptr_t)img_dos_header + rva_name[i]);
        const uint64_t get_hash = t1ha0(api_name, len, seed);
        if (api_hash == get_hash) {
            ord = static_cast<uint64_t>(rva_ordinal[i]);
            break;
        }
    }
    const auto func_addr = (PDWORD)((uintptr_t)img_dos_header + in_export->AddressOfFunctions);
    const auto func_find = (LPVOID)((uintptr_t)img_dos_header + func_addr[ord]);
    return func_find;
}

__forceinline LPVOID getApi(uint64_t api_hash, std::string module, uint64_t len, const uint64_t seed) {
    HMODULE krnl32, hDll;
    LPVOID api_func;

    //x64 only
    const auto ModuleList = 0x18;
    const auto ModuleListFlink = 0x18;
    const auto KernelBaseAddr = 0x10;
    const intptr_t peb = __readgsqword(0x60);

    const auto mdllist = *(intptr_t *)(peb + ModuleList);
    const auto mlink = *(intptr_t*)(mdllist + ModuleListFlink);
    auto krnbase = *(intptr_t*)(mlink + KernelBaseAddr);
    auto mdl = (LDR_MODULE *)mlink;
    HMODULE hKernel32 = NULL;
    hKernel32 = _getKernel32Handle();

    do {
        mdl = (LDR_MODULE *)mdl->e[0].Flink;
        if (mdl->base != nullptr) {
            if (Tools::CRT::String::myStrStr((char*)Tools::CRT::String::ws2s(mdl->dllname.Buffer).c_str(), (char*)"kernel32.dll") != NULL) {
                break;
            }
        }
    }
    while (mlink != (intptr_t)mdl);

    krnl32 = static_cast<HMODULE>(mdl->base);

    const char* LoadLibraryA_ = "LoadLibraryA";
    const uint64_t api_hash_LoadLibraryA = t1ha0(LoadLibraryA_, strlen(LoadLibraryA_), STRONG_SEED);
    temp_LoadLibraryA = static_cast<HMODULE(WINAPI*)(LPCSTR)>(parseExportTable(krnl32, api_hash_LoadLibraryA, strlen(LoadLibraryA_), STRONG_SEED));
    hDll = Tools::Utils::getModule(module);
    //Sanity check, incase it somehow fails load it the old way
    if (!hDll) 
        hDll = temp_LoadLibraryA(module.c_str());

    api_func = static_cast<LPVOID>(parseExportTable(hDll, api_hash, len, seed));

    return api_func;
}
