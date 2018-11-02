/*
*
* WFEx - Warframe script engine extention made for
* simulating player behaviour, extending UI and/or
* manipulating in-game objects.
*
*/

#ifndef _REDECL_H
#define _REDECL_H

/*
* Function trampoline target re-declarations
*/

inline lua_State *(__cdecl newstate_f)(lua_Alloc f, void * ud)
{
	assert(Pointers->newstate != nullptr);
	Libcore::MasterState = Pointers->newstate(f, ud);
	Libcore::LibState = Pointers->newthread(Libcore::MasterState);

	WRITE << "Master state preserved at " << std::hex << Libcore::MasterState << " and new thread created at " << std::hex << Libcore::LibState << NL;

	return Libcore::MasterState;
}

inline int (__cdecl load_f)(lua_State * L, lua_Reader reader, void* data, const char * chunkname) {

	LoadObject * lo = static_cast<LoadObject *>(data);
	if (!chunkname) {
		if (lo->size > 0) {
			WriteBinary(lo, chunkname);
		}
	}

	return Pointers->load(L, reader, data, chunkname);
}

inline lua_State * newthread_f(lua_State * L)
{
	return nullptr;
}

/*
 * Basic initializators
 */

inline void WritePointers()
{
	std::shared_ptr<METINF> element;

	// newstate
	element = Libcore::FindFunction("lua_newstate");
	if (element->Point(Pointers->newstate) == 0)
		WRITE << element->Label << " pointed successfully." << NL;

	// newthread
	element = Libcore::FindFunction("lua_newthread");
	if (element->Point(Pointers->newthread) == 0)
		WRITE << element->Label << " pointed successfully." << NL;

	// luaL_loadstring
	element = Libcore::FindFunction("luaL_loadstring");
	if (element->Point(Pointers->loadstring) == 0)
		WRITE << element->Label << " pointed successfully." << NL;

	// luaL_loadfile
	element = Libcore::FindFunction("luaL_loadfile");
	if (element->Point(Pointers->loadfile) == 0)
		WRITE << element->Label << " pointed successfully." << NL;

	// lua_load
	element = Libcore::FindFunction("lua_load");
	if (element->Point(Pointers->load) == 0)
		WRITE << element->Label << " pointed successfully." << NL;

	// lua_pushcclosure
	element = Libcore::FindFunction("lua_pushcclosure");
	if(element->Point(Pointers->pushcclosure) == 0)
		WRITE << element->Label << " pointed successfully." << NL;

	// lua_pcall
	element = Libcore::FindFunction("lua_pcall");
	if (element->Point(Pointers->pcall) == 0)
		WRITE << element->Label << " pointed successfully." << NL;

	return;
}

inline void WriteDetours()
{
	WRITE << "Detouring lua_newstate." << NL;
	Detour(Pointers->newstate, reinterpret_cast<PBYTE>(newstate_f));

	WRITE << "Detouring lua_load." << NL;
	Detour(Pointers->load, reinterpret_cast<PBYTE>(load_f));
	
	return;
}

#endif