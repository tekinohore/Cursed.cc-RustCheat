#define in_range(x, a, b) (x >= a && x <= b)
#define get_bits(x) (in_range((x & (~0x20)), 'A', 'F') ? ((x & (~0x20)) - 'A' + 0xA): (in_range(x, '0', '9') ? x - '0': 0))
#define get_byte(x) (get_bits(x[0]) << 4 | get_bits(x[1]))
#include <d2d1helper.h>

inline D2D1::ColorF ConverToRGB(float R, float G, float B)
{
	return (D2D1::ColorF::ColorF(R / 255.f, G / 255.f, B / 255.f));
}


DWORD64 FindPattern(const wchar_t* module, const char* pattern)
{
	MODULEINFO mod;
	HANDLE CurProc = FC(kernel32, GetCurrentProcess);
	FC(kernel32, K32GetModuleInformation, CurProc, (HMODULE)GetModBase(module), &mod, sizeof(MODULEINFO));
	uintptr_t start = (uintptr_t)mod.lpBaseOfDll;
	uintptr_t end = (uintptr_t)mod.lpBaseOfDll + (uintptr_t)mod.SizeOfImage;
	uintptr_t match = 0;
	const char* current = pattern;

	for (uintptr_t pCur = start; pCur < end; pCur++)
	{
		if (!*current)
			return match;

		if (*(PBYTE)current == ('\?') || *(BYTE*)pCur == get_byte(current))
		{
			if (!match)
				match = pCur;

			if (!current[2])
				return match;

			if (*(PWORD)current == ('\?\?') || *(PBYTE)current != ('\?'))
				current += 3;
			else
				current += 2;
		}
		else
		{
			current = pattern;
			match = 0;
		}
	}

	return 0;
}

void CreateThreadSafe(PVOID StartAddr)
{
	typedef HANDLE(__fastcall* CreateSimpleThreadFn)(void*, PVOID, PVOID, unsigned int);
	static CreateSimpleThreadFn CST = nullptr;
	CST = (CreateSimpleThreadFn)FindPattern((PBYTE)"\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x48\x89\x74\x24\x00\x57\x48\x83\xEC\x30", StrA("xxxx?xxxx?xxxx?xxxxx"), StrW(L"tier0_s64.dll"));
	CST(StartAddr, 0, 0, 0);
}