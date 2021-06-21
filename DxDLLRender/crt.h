#pragma once

char* __cdecl m_strstr(const char* str1, const char* str2)
{
	if (!str1)
		return (0);
	char* cp = (char*)str1;
	char* s1, * s2;

	if (!*str2)
		return((char*)str1);

	while (*cp)
	{
		s1 = cp;
		s2 = (char*)str2;

		while (*s1 && *s2 && !(*s1 - *s2))
			s1++, s2++;

		if (!*s2)
			return(cp);

		cp++;
	}

	return(0);
}
unsigned int m_strlen(char* str)
{
	int cnt = 0;
	if (!str)
		return 0;
	for (; *str != '\0'; ++str)
		++cnt;
	return cnt;
}
unsigned int m_wcslen(wchar_t* str)
{
	int cnt = 0;
	if (!str)
		return 0;
	for (; *str != '\0'; ++str)
		++cnt;
	return cnt;
}
bool m_wcsicmp(wchar_t* a, const wchar_t* b) {

	int ret = 0;
	wchar_t* p1 = (wchar_t*)a;
	wchar_t* p2 = (wchar_t*)b;
	while (!(ret = *p1 - *p2) && *p2)
		++p1, ++p2;

	return ret == 0;
}

bool m_strcmp(char* a, char* b) {
	if (!a || !b) return !a && !b;

	int ret = 0;
	unsigned char* p1 = (unsigned char*)a;
	unsigned char* p2 = (unsigned char*)b;
	while (!(ret = *p1 - *p2) && *p2)
		++p1, ++p2;

	return ret == 0;
}

unsigned short lfsr = 0xACE1u;
unsigned int bit = 0;

unsigned random()
{
	if (!lfsr) {
		lfsr = 0xACE1u; bit = 0;
	}
	bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
	return lfsr = (lfsr >> 1) | (bit << 15);
}

namespace rust {
	template<typename T>
	class list {
	public:
		T get(uint32_t idx)
		{
			const auto internal_list = reinterpret_cast<uintptr_t>(this + 0x20);
			return *reinterpret_cast<T*>(internal_list + idx * sizeof(T));
		}

		T get_value(uint32_t idx)
		{
			const auto list = *reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x10);
			const auto internal_list = list + 0x20;
			return *reinterpret_cast<T*>(internal_list + idx * sizeof(T));
		}

		T operator[](uint32_t idx) { return get(idx); }

		const uintptr_t get_size() { return *reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x18); }

		template<typename F>
		void for_each(const F callback)
		{
			for (auto i = 0; i < get_size(); i++) {
				auto object = this->get(i);
				if (!object)
					continue;
				callback(object, i);
			}
		}
	};

	enum class ModelState_Flag
	{
		Ducked = 1,
		Jumped = 2,
		OnGround = 4,
		Sleeping = 8,
		Sprinting = 16,
		Flying = 64,
		Aiming = 128,
		Prone = 256,
		Mounted = 512,
		Relaxed = 1024,
	};

	namespace classes {
		enum class layer : uint32_t {
			Default = 0,
			TransparentFX = 1,
			Ignore_Raycast = 2,
			Reserved1 = 3,
			Water = 4,
			UI = 5,
			Reserved2 = 6,
			Reserved3 = 7,
			Deployed = 8,
			Ragdoll = 9,
			Invisible = 10,
			AI = 11,
			PlayerMovement = 12,
			Vehicle_Detailed = 13,
			Game_Trace = 14,
			Vehicle_World = 15,
			World = 16,
			Player_Server = 17,
			Trigger = 18,
			Player_Model_Rendering = 19,
			Physics_Projectile = 20,
			Construction = 21,
			Construction_Socket = 22,
			Terrain = 23,
			Transparent = 24,
			Clutter = 25,
			Debris = 26,
			Vehicle_Large = 27,
			Prevent_Movement = 28,
			Prevent_Building = 29,
			Tree = 30,
			Unused2 = 31
		};
		class string {
		public:
			char zpad[0x10];

			int size;
			wchar_t str[128 + 1];
			string(const wchar_t* st) {
				size = min(m_wcslen((wchar_t*)st), 128);
				for (int i = 0; i < size; i++) {
					str[i] = st[i];
				}
				str[size] = 0;
			}
		};
		class list {
		public:
			template <typename T>
			T get_value() {
				auto list = *reinterpret_cast<uintptr_t*>(this + 0x10);
				if (!list)
					return 0;

				auto value = *reinterpret_cast<T*>(list + 0x28);
				if (!value)
					return 0;
				return value;
			}

			int get_size() {
				auto value = get_value<uintptr_t>();
				if (!value)
					return 0;

				auto size = safe_read(value + 0x10, int);
				if (!size)
					return 0;
			}

			template <typename T>
			T get_buffer() {
				auto value = get_value<uintptr_t>();

				return *reinterpret_cast<uintptr_t*>(value + 0x18);
			}
		};
	}
	typedef struct Str2
	{
		char stub[0x10];
		int len;
		wchar_t str[1];
	} *str;
}

template<typename T>
class list {
public:

	T get(uint32_t idx)
	{
		const auto internal_list = reinterpret_cast<uintptr_t>(this + 0x20);
		return *reinterpret_cast<T*>(internal_list + idx * sizeof(T));
	}

	T get_value(uint32_t idx)
	{
		const auto list = *reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x10);
		const auto internal_list = list + 0x20;
		return *reinterpret_cast<T*>(internal_list + idx * sizeof(T));
	}

	T operator[](uint32_t idx) { return get(idx); }

	const uint32_t get_size() { return *reinterpret_cast<uint32_t*>((uintptr_t)this + 0x18); }

	template<typename F>
	void for_each(const F callback)
	{
		for (auto i = 0; i < get_size(); i++) {
			auto object = this->get(i);
			if (!object)
				continue;
			callback(object, i);
		}
	}
};
