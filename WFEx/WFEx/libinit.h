/*
 *
 * WFEx - Warframe script engine extention made for
 * simulating player behaviour, extending UI and/or
 * manipulating in-game objects.
 *
 */

#ifndef _LIBINIT_H
#define _LIBINIT_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <memory>

#include <assert.h>
#include <string.h>
#include <Windows.h>
#include <Psapi.h>

extern "C" {
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

#define GAME_HANDLE GetModuleHandle(L"Warframe.exe")

#define HOME_DIR "C:\\.dev\\ws_intercept\\WFEx\\"
#define lib_Directory HOME_DIR "Logs\\"
#define lib_Data HOME_DIR "Data\\"

#include "objects.h"
#include "libcore.h"
#include "utility.h"
#include "trampoline.h"

#endif