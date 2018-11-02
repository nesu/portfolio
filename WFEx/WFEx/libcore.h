/*
*
* WFEx - Warframe script engine extention made for
* simulating player behaviour, extending UI and/or
* manipulating in-game objects.
*
*/

#ifndef _LIBCORE_H
#define _LIBCORE_H

#include <map>
#include "libinit.h"

class Libcore
{
	public:
		static void Initialize(const std::shared_ptr<LIBINF>& libi, const std::shared_ptr<GMINF>& gmi);

	private:
		static std::shared_ptr<GMINF> gm_Information;
		static std::shared_ptr<LIBINF> lib_Information;

		/* Function elements */
		static std::vector<std::shared_ptr<METINF>> Methods;

	/*	Game function control	*/
	public:
		static void Registry();

		static void FindPattern(const std::shared_ptr<METINF>& metinf);
		static std::shared_ptr<METINF> FindFunction(std::string label);

	/*	Game elements */
		static lua_State * MasterState;
		static lua_State * LibState;

};

#endif