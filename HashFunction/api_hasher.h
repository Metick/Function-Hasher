#ifndef VORPAL_API_HASHER_H
#define VORPAL_API_HASHER_H

#include <Windows.h>
#include <codecvt>
#include <winternl.h>

namespace vorpal_api_hasher
{
#define RECORD(address, type, field) \
	  ((type*)((char*)(address) - (ULONGLONG)(&((type*)0)->field)))

	struct _STRING64
	{
		USHORT Length; // 0x0
		USHORT MaximumLength; // 0x2
		ULONGLONG Buffer; // 0x8
	};

	typedef struct _PEB64
	{
		UCHAR InheritedAddressSpace; // 0x0
		UCHAR ReadImageFileExecOptions; // 0x1
		UCHAR BeingDebugged; // 0x2
		union
		{
			UCHAR BitField; // 0x3
			struct
			{
				UCHAR ImageUsesLargePages : 1; // 0x3
				UCHAR IsProtectedProcess : 1; // 0x3
				UCHAR IsImageDynamicallyRelocated : 1; // 0x3
				UCHAR SkipPatchingUser32Forwarders : 1; // 0x3
				UCHAR IsPackagedProcess : 1; // 0x3
				UCHAR IsAppContainer : 1; // 0x3
				UCHAR IsProtectedProcessLight : 1; // 0x3
				UCHAR IsLongPathAwareProcess : 1; // 0x3
			};
		};

		UCHAR Padding0[4]; // 0x4
		ULONGLONG Mutant; // 0x8
		ULONGLONG ImageBaseAddress; // 0x10
		PPEB_LDR_DATA Ldr; // 0x18
		ULONGLONG ProcessParameters; // 0x20
		ULONGLONG SubSystemData; // 0x28
		ULONGLONG ProcessHeap; // 0x30
		ULONGLONG FastPebLock; // 0x38
		ULONGLONG AtlThunkSListPtr; // 0x40
		ULONGLONG IFEOKey; // 0x48
		union
		{
			ULONG CrossProcessFlags; // 0x50
			struct
			{
				ULONG ProcessInJob : 1; // 0x50
				ULONG ProcessInitializing : 1; // 0x50
				ULONG ProcessUsingVEH : 1; // 0x50
				ULONG ProcessUsingVCH : 1; // 0x50
				ULONG ProcessUsingFTH : 1; // 0x50
				ULONG ProcessPreviouslyThrottled : 1; // 0x50
				ULONG ProcessCurrentlyThrottled : 1; // 0x50
				ULONG ProcessImagesHotPatched : 1; // 0x50
				ULONG ReservedBits0 : 24; // 0x50
			};
		};

		UCHAR Padding1[4]; // 0x54
		union
		{
			ULONGLONG KernelCallbackTable; // 0x58
			ULONGLONG UserSharedInfoPtr; // 0x58
		};

		ULONG SystemReserved; // 0x60
		ULONG AtlThunkSListPtr32; // 0x64
		ULONGLONG ApiSetMap; // 0x68
		ULONG TlsExpansionCounter; // 0x70
		UCHAR Padding2[4]; // 0x74
		ULONGLONG TlsBitmap; // 0x78
		ULONG TlsBitmapBits[2]; // 0x80
		ULONGLONG ReadOnlySharedMemoryBase; // 0x88
		ULONGLONG SharedData; // 0x90
		ULONGLONG ReadOnlyStaticServerData; // 0x98
		ULONGLONG AnsiCodePageData; // 0xa0
		ULONGLONG OemCodePageData; // 0xa8
		ULONGLONG UnicodeCaseTableData; // 0xb0
		ULONG NumberOfProcessors; // 0xb8
		ULONG NtGlobalFlag; // 0xbc
		union _LARGE_INTEGER CriticalSectionTimeout; // 0xc0
		ULONGLONG HeapSegmentReserve; // 0xc8
		ULONGLONG HeapSegmentCommit; // 0xd0
		ULONGLONG HeapDeCommitTotalFreeThreshold; // 0xd8
		ULONGLONG HeapDeCommitFreeBlockThreshold; // 0xe0
		ULONG NumberOfHeaps; // 0xe8
		ULONG MaximumNumberOfHeaps; // 0xec
		ULONGLONG ProcessHeaps; // 0xf0
		ULONGLONG GdiSharedHandleTable; // 0xf8
		ULONGLONG ProcessStarterHelper; // 0x100
		ULONG GdiDCAttributeList; // 0x108
		UCHAR Padding3[4]; // 0x10c
		ULONGLONG LoaderLock; // 0x110
		ULONG OSMajorVersion; // 0x118
		ULONG OSMinorVersion; // 0x11c
		USHORT OSBuildNumber; // 0x120
		USHORT OSCSDVersion; // 0x122
		ULONG OSPlatformId; // 0x124
		ULONG ImageSubsystem; // 0x128
		ULONG ImageSubsystemMajorVersion; // 0x12c
		ULONG ImageSubsystemMinorVersion; // 0x130
		UCHAR Padding4[4]; // 0x134
		ULONGLONG ActiveProcessAffinityMask; // 0x138
		ULONG GdiHandleBuffer[60]; // 0x140
		ULONGLONG PostProcessInitRoutine; // 0x230
		ULONGLONG TlsExpansionBitmap; // 0x238
		ULONG TlsExpansionBitmapBits[32]; // 0x240
		ULONG SessionId; // 0x2c0
		UCHAR Padding5[4]; // 0x2c4
		union _ULARGE_INTEGER AppCompatFlags; // 0x2c8
		union _ULARGE_INTEGER AppCompatFlagsUser; // 0x2d0
		ULONGLONG pShimData; // 0x2d8
		ULONGLONG AppCompatInfo; // 0x2e0
		struct _STRING64 CSDVersion; // 0x2e8
		ULONGLONG ActivationContextData; // 0x2f8
		ULONGLONG ProcessAssemblyStorageMap; // 0x300
		ULONGLONG SystemDefaultActivationContextData; // 0x308
		ULONGLONG SystemAssemblyStorageMap; // 0x310
		ULONGLONG MinimumStackCommit; // 0x318
		ULONGLONG SparePointers[4]; // 0x320
		ULONG SpareUlongs[5]; // 0x340
		ULONGLONG WerRegistrationData; // 0x358
		ULONGLONG WerShipAssertPtr; // 0x360
		ULONGLONG pUnused; // 0x368
		ULONGLONG pImageHeaderHash; // 0x370
		union
		{
			ULONG TracingFlags; // 0x378
			struct
			{
				ULONG HeapTracingEnabled : 1; // 0x378
				ULONG CritSecTracingEnabled : 1; // 0x378
				ULONG LibLoaderTracingEnabled : 1; // 0x378
				ULONG SpareTracingBits : 29; // 0x378
			};
		};

		UCHAR Padding6[4]; // 0x37c
		ULONGLONG CsrServerReadOnlySharedMemoryBase; // 0x380
		ULONGLONG TppWorkerpListLock; // 0x388
		struct LIST_ENTRY64 TppWorkerpList; // 0x390
		ULONGLONG WaitOnAddressHashTable[128]; // 0x3a0
		ULONGLONG TelemetryCoverageHeader; // 0x7a0
		ULONG CloudFileFlags; // 0x7a8
		ULONG CloudFileDiagFlags; // 0x7ac
		CHAR PlaceholderCompatibilityMode; // 0x7b0
		CHAR PlaceholderCompatibilityModeReserved[7]; // 0x7b1
		ULONGLONG LeapSecondData; // 0x7b8
		union
		{
			ULONG LeapSecondFlags; // 0x7c0
			struct
			{
				ULONG SixtySecondEnabled : 1; // 0x7c0
				ULONG Reserved : 31; // 0x7c0
			};
		};

		ULONG NtGlobalFlag2; // 0x7c4
	} PEB64, *PPEB64;

	typedef struct _RTL_BALANCED_NODE
	{
		union
		{
			struct _RTL_BALANCED_NODE* Children[2]; // 0x0
			struct
			{
				struct _RTL_BALANCED_NODE* Left; // 0x0
				struct _RTL_BALANCED_NODE* Right; // 0x8
			};
		};

		union
		{
			struct
			{
				UCHAR Red : 1; // 0x10
				UCHAR Balance : 2; // 0x10
			};

			ULONGLONG ParentValue; // 0x10
		};
	} RTL_BALANCED_NODE, *PRTL_BALANCED_NODE;

	typedef struct _FULL_LDR_DATA_TABLE_ENTRY
	{
		struct _LIST_ENTRY InLoadOrderLinks; // 0x0
		struct _LIST_ENTRY InMemoryOrderLinks; // 0x10
		struct _LIST_ENTRY InInitializationOrderLinks; // 0x20
		VOID* DllBase; // 0x30
		VOID* EntryPoint; // 0x38
		ULONG SizeOfImage; // 0x40
		struct _UNICODE_STRING FullDllName; // 0x48
		struct _UNICODE_STRING BaseDllName; // 0x58
		union
		{
			UCHAR FlagGroup[4]; // 0x68
			ULONG Flags; // 0x68
			struct
			{
				ULONG PackagedBinary : 1; // 0x68
				ULONG MarkedForRemoval : 1; // 0x68
				ULONG ImageDll : 1; // 0x68
				ULONG LoadNotificationsSent : 1; // 0x68
				ULONG TelemetryEntryProcessed : 1; // 0x68
				ULONG ProcessStaticImport : 1; // 0x68
				ULONG InLegacyLists : 1; // 0x68
				ULONG InIndexes : 1; // 0x68
				ULONG ShimDll : 1; // 0x68
				ULONG InExceptionTable : 1; // 0x68
				ULONG ReservedFlags1 : 2; // 0x68
				ULONG LoadInProgress : 1; // 0x68
				ULONG LoadConfigProcessed : 1; // 0x68
				ULONG EntryProcessed : 1; // 0x68
				ULONG ProtectDelayLoad : 1; // 0x68
				ULONG ReservedFlags3 : 2; // 0x68
				ULONG DontCallForThreads : 1; // 0x68
				ULONG ProcessAttachCalled : 1; // 0x68
				ULONG ProcessAttachFailed : 1; // 0x68
				ULONG CorDeferredValidate : 1; // 0x68
				ULONG CorImage : 1; // 0x68
				ULONG DontRelocate : 1; // 0x68
				ULONG CorILOnly : 1; // 0x68
				ULONG ChpeImage : 1; // 0x68
				ULONG ReservedFlags5 : 2; // 0x68
				ULONG Redirected : 1; // 0x68
				ULONG ReservedFlags6 : 2; // 0x68
				ULONG CompatDatabaseProcessed : 1; // 0x68
			};
		};

		USHORT ObsoleteLoadCount; // 0x6c
		USHORT TlsIndex; // 0x6e
		struct _LIST_ENTRY HashLinks; // 0x70
		ULONG TimeDateStamp; // 0x80
		struct _ACTIVATION_CONTEXT* EntryPointActivationContext; // 0x88
		VOID* Lock; // 0x90
		struct _LDR_DDAG_NODE* DdagNode; // 0x98
		struct _LIST_ENTRY NodeModuleLink; // 0xa0
		struct _LDRP_LOAD_CONTEXT* LoadContext; // 0xb0
		VOID* ParentDllBase; // 0xb8
		VOID* SwitchBackContext; // 0xc0
		struct _RTL_BALANCED_NODE BaseAddressIndexNode; // 0xc8
		struct _RTL_BALANCED_NODE MappingInfoIndexNode; // 0xe0
		ULONGLONG OriginalBase; // 0xf8
		union _LARGE_INTEGER LoadTime; // 0x100
		ULONG BaseNameHashValue; // 0x108
		enum _LDR_DLL_LOAD_REASON LoadReason; // 0x10c
		ULONG ImplicitPathOptions; // 0x110
		ULONG ReferenceCount; // 0x114
		ULONG DependentLoadFlags; // 0x118
		UCHAR SigningLevel; // 0x11c
	} FULL_LDR_DATA_TABLE_ENTRY, *PFULL_LDR_DATA_TABLE_ENTRY;

	//turn off optimnizations
#pragma optimize("", off)

#define COMPILE_TIME_RANDOM_SEED \
    (unsigned)(__TIME__[7] - '0' + __TIME__[6] - '0' + __TIME__[4] - '0' + \
               __TIME__[3] - '0' + __TIME__[1] - '0' + __TIME__[0] - '0' + \
               __FILE__[sizeof(__FILE__) - 1] - '0' + (__LINE__ % 100) + __COUNTER__ + (7 * __COUNTER__))
#define COMPILE_TIME_RANDOM_NUMBER \
	(unsigned)( (((__TIME__[6] - '0') * 10 + (7 * __COUNTER__)) + (__TIME__[7] - '0')) % 10) * __COUNTER__

	template <unsigned N, unsigned Seed>
	struct random_generator
	{
		static constexpr unsigned value = (1103515245 * random_generator<N - 1, Seed>::value + 12345) % 0x80000000u;
	};

	template <unsigned Seed>
	struct random_generator<0, Seed>
	{
		static constexpr unsigned value = Seed;
	};

	__forceinline constexpr unsigned generate_compile_time_seed()
	{
		return random_generator<COMPILE_TIME_RANDOM_NUMBER, COMPILE_TIME_RANDOM_SEED>::value; // 1 is a placeholder for runtime seed
	}

	template <uint64_t Seed>
	class hash_import
	{
	public:
		__forceinline static LPVOID parse_eat_table(const uintptr_t base, const uint64_t api_hash);

		__forceinline static uintptr_t get_import(const uint64_t hash)
		{
			PEB64* peb = (PEB64*)__readgsqword(0x60);
			LIST_ENTRY* head = &peb->Ldr->InMemoryOrderModuleList;
			for (auto curr = head->Flink; curr != head; curr = curr->Flink)
			{
				auto entry = RECORD(curr, FULL_LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);
				uintptr_t func = reinterpret_cast<uintptr_t>(parse_eat_table(reinterpret_cast<uintptr_t>(entry->DllBase), hash));
				if (func) return func;
			}
			return 0;
		}
	};

	template <uint64_t Seed>
	struct compile_time_hash_impl
	{
		__forceinline static constexpr uint32_t TO_UPPERCASE(char c)
		{
			return (c >= 'a' && c <= 'z') ? (c - 'a' + 'A') : c;
		}

		__forceinline static constexpr uint64_t Hash(const char* str, uint32_t index = 0)
		{
			return !str[index] ? Seed : ((compile_time_hash_impl<Seed>::Hash(str, index + 1) * 33) << 16 >> 16 ^ TO_UPPERCASE(str[index]));
		}
	};

	//This is a cheap way to fix msvc compiler's optimizations that will optimize this away :( 
	template <uint64_t Seed>
	LPVOID hash_import<Seed>::parse_eat_table(const uintptr_t base, const uint64_t api_hash)
	{
		auto dos = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
		auto nt = reinterpret_cast<IMAGE_NT_HEADERS*>(base + dos->e_lfanew);

		auto dir = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
		if (!dir.VirtualAddress) return 0;

		auto eat = reinterpret_cast<IMAGE_EXPORT_DIRECTORY*>(base + dir.VirtualAddress);
		uint32_t* functions = reinterpret_cast<uint32_t*>(base + eat->AddressOfFunctions);
		uint32_t* names = reinterpret_cast<uint32_t*>(base + eat->AddressOfNames);
		uint16_t* ordinals = reinterpret_cast<uint16_t*>(base + eat->AddressOfNameOrdinals);

		for (uint32_t i = 0; i < eat->NumberOfNames; ++i)
		{
			const char* name = reinterpret_cast<char*>(base + names[i]);
			const uint64_t hash = compile_time_hash_impl<Seed>::Hash(name);
			if (hash == api_hash)
			{
				return (LPVOID)(base + functions[ordinals[i]]);
			}
		}
		return (0);
	}

#pragma optimize("", on)
}

#define HASH(func, seed) \
[]() { \
    constexpr static uint64_t h = vorpal_api_hasher::compile_time_hash_impl<seed>::Hash(func); \
    return h; \
}()
#define IMPORT_HASH(func) \
[]() {\
	constexpr unsigned int seed = vorpal_api_hasher::generate_compile_time_seed();\
	return reinterpret_cast<decltype(&func)>(vorpal_api_hasher::hash_import<seed>::get_import(HASH(###func, seed)));\
}()

#endif
