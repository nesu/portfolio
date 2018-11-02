/*
*
* WFEx - Warframe script engine extention made for
* simulating player behaviour, extending UI and/or
* manipulating in-game objects.
*
*/

#ifndef _WFEX_UTILITY_H
#define _WFEX_UTILITY_H

std::string			Timestamp();
std::ofstream		getWriter(bool TRUNCATE = false);

#define NL		(std::endl)
#define WRITE	(getWriter() << Timestamp().c_str())

void				WriteBinary(LoadObject * lobj, const char * chunkname);

#endif