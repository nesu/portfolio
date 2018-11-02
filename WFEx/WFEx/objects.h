/*
*
* WFEx - Warframe script engine extention made for
* simulating player behaviour, extending UI and/or
* manipulating in-game objects.
*
*/

#ifndef _OBJECTS_H
#define _OBJECTS_H

typedef struct game_cx
{
	HMODULE Handle;
	MODULEINFO Information;

	game_cx() :
		Handle(GAME_HANDLE)
	{
		GetModuleInformation(GetCurrentProcess(), Handle, &Information, sizeof(Information));
		return;
	}

	LPVOID Base() const
	{
		return Information.lpBaseOfDll;
	}

	DWORD Size() const
	{
		return Information.SizeOfImage;
	}

} GMINF;

typedef struct library_cx
{
	HMODULE Handle;
	MODULEINFO Information;

	std::ofstream lib_Writer;

	library_cx():
		Handle(nullptr)
	{
	}

	explicit library_cx(HMODULE libh) :
		Handle(libh)
	{
		GetModuleInformation(GetCurrentProcess(), libh, &Information, sizeof(Information));
		return;
	}

} LIBINF;

typedef struct method_cx
{
	std::string Label;
	std::string Pattern;
	std::string Mask;

	char *GetBytes() const
	{
		std::istringstream hexstr(Pattern);
		std::vector<unsigned char> bytes;

		unsigned int byte;
		while (hexstr >> std::hex >> byte)
		{
			bytes.push_back(byte);
		}

		auto buffer = new char[bytes.size()];
		std::copy(bytes.begin(), bytes.end(), buffer);

		hexstr.clear();
		bytes.clear();

		return buffer;
	}

	template<typename _Ty>
	int Point(_Ty &_ptr)
	{
		if (!Valid)
			return 1;

		_ptr = reinterpret_cast<_Ty>(reinterpret_cast<DWORD>(Address));
		if (reinterpret_cast<LPVOID>(_ptr) != Address)
			return 1;

		// TODO: Kokią nors patikrą įstatyt..
		return 0;
	}

	LPVOID Address;
	BOOL Valid;

	method_cx()
	{
		Valid = FALSE;
		Address = nullptr;
	}

} METINF;

struct LoadObject {
	const char * s;
	size_t size;
};

#endif