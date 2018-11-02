/*
*
* WFEx - Warframe script engine extention made for
* simulating player behaviour, extending UI and/or
* manipulating in-game objects.
*
*/

#include "libinit.h"
#include "redecl.h"

void Thread();

std::shared_ptr<PTRHND> Pointers = std::make_shared<PTRHND>();

BOOL APIENTRY DllMain(HMODULE module, DWORD call_reason, LPVOID reserved)
{
	if (call_reason != DLL_PROCESS_ATTACH)
		return TRUE;

	getWriter(true);

	auto LiS = std::make_shared<LIBINF>(module);
	auto GmS = std::make_shared<GMINF>();

	Libcore::Initialize(LiS, GmS);
	Libcore::Registry();

	CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Thread), nullptr, 0, nullptr);
	return TRUE;
}

extern "C" int luaF_redis(lua_State * L)
{
	WRITE << "luaF_redis reached." << NL;
	return 1;
}

void Subthread()
{
	Sleep(10000);
	lua_State * thState = Pointers->newthread(Libcore::MasterState);
	if(Pointers->loadfile(thState, lib_Data "Scripts\\WFEx.lua"))
	{
		WRITE << "Error loading WFEx.lua file." << NL;
	}

	//Pointers->loadfile(thState, "D:\\.reversing\\WFEx\\Data\\Scripts\\internal.lua");
	//Pointers->loadfile(thState, "D:\\.reversing\\WFEx\\Data\\Scripts\\showmessage.lua");
	Pointers->pcall(thState, 0, LUA_MULTRET, 0);
	ExitThread(0);

	
}

void Thread()
{
	WRITE << "Writing game function pointers." << NL;
	WritePointers();

	WRITE << "Writing pointed function detours." << NL;
	WriteDetours();

	while (Libcore::MasterState == nullptr || Libcore::LibState == nullptr)
		Sleep(50);

	WRITE << "Injected library has finished initializations." << NL;
	CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Subthread), nullptr, 0, nullptr);
	ExitThread(0);
}