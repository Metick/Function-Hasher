#pragma once
namespace Tools {
    namespace CRT {
        namespace String {
            extern inline unsigned int _strnlen_s(const char* str, size_t maxsize);

            extern char* myStrncpy(char* dst, const char* src, unsigned long long num);

            extern int myStrncmp(const char* s1, const char* s2, size_t n);

            extern char* myStrStr(char* str, char* substr);

            extern std::string ws2s(const std::wstring& wstr);
        }

        namespace Memory {

            extern void* myMemset(void* dst, int val, size_t size);

            extern void myMemcpy(void* dst, void* src, size_t size);
        }
    }
}

#define myRtlZeroMemory(Destination,Length) Tools::CRT::Memory::myMemset((Destination),0,(Length))