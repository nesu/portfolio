/*
*
* WFEx - Warframe script engine extension made for
* simulating player behaviour, extending UI and/or
* manipulating in-game objects.
*
*/

#ifndef _TRAMPOLINE_H
#define _TRAMPOLINE_H

#include <type_traits>
#include "detours.h"

/*
* Function pointer type declarations
*/

//typedef lua_State * (__cdecl * newstate_t)(lua_Alloc f, void *ud);

using newstate_t = std::add_pointer<lua_State *(lua_Alloc f, void * ud)>::type;
using newthread_t = std::add_pointer<lua_State *(lua_State * L)>::type;
using pcall_t = std::add_pointer<int(lua_State * L, int nargs, int nresults, int errfunc)>::type;
using pushcclosure_t = std::add_pointer<void(lua_State * L, lua_CFunction fn, int n)>::type;
using setfield_t = std::add_pointer<void(lua_State * L, int idx, const char * k)>::type;

using loadstring_t = std::add_pointer<int(lua_State * L, const char * s)>::type;
using loadfile_t = std::add_pointer<int(lua_State * L, const char * filename)>::type;
using load_t = std::add_pointer<int(lua_State * L, lua_Reader reader, void * data, const char * chunkname)>::type;

/*
* Trampoline control
*/

typedef struct pointer_map
{
	newstate_t newstate;
	newthread_t newthread;
	pushcclosure_t pushcclosure;
	pcall_t pcall;
	load_t load;

	// dostring
	loadstring_t loadstring;

	// dofile
	loadfile_t loadfile;

	// setglobal
	setfield_t setfield;

	pointer_map():
		newstate(nullptr),
		newthread(nullptr),
		pushcclosure(nullptr),
		pcall(nullptr), 
		loadstring(nullptr),
		loadfile(nullptr),
		setfield(nullptr),
		load(nullptr)
	{
	}


} PTRHND;

/* Hooked function pointers. */
extern std::shared_ptr<PTRHND> Pointers;

template<typename _Ty>
inline void Detour(_Ty& fn_ptr, PBYTE trampoline)
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	fn_ptr = reinterpret_cast<_Ty>(DetourAttach(&reinterpret_cast<PVOID&>(fn_ptr), trampoline));
	DetourTransactionCommit();
}


#endif