/*
*
* WFEx - Warframe script engine extention made for
* simulating player behaviour, extending UI and/or
* manipulating in-game objects.
*
*/

#include <ctime>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <algorithm>

#include "boost\format.hpp"
#include "libinit.h"

bool writer_Start = false;

std::string Timestamp()
{
	std::stringstream ss;
	auto now = std::chrono::system_clock::now();
	auto now_c = std::chrono::system_clock::to_time_t(now);
	ss << std::put_time(std::localtime(&now_c), "%H:%M:%S") << " | ";
	return ss.str();
}

std::ofstream getWriter(bool TRUNCATE)
{
	std::ofstream ofstr;
	int flags = (TRUNCATE) ? std::ios_base::out : std::ios_base::app;
	ofstr.open(lib_Directory "Writer.log", flags);
	return ofstr;
}

std::string generateRandomString(size_t length)
{
	const char* charmap = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const size_t charmapLength = strlen(charmap);
	auto generator = [&]() { return charmap[rand() % charmapLength]; };
	std::string result;
	result.reserve(length);
	generate_n(back_inserter(result), length, generator);
	return result;
}

void WriteBinary(LoadObject * lobj, const char * chunkname) {
	
	using boost::format;
	using boost::io::group;

	std::string binary = str(format(lib_Data "Binary\\B%1%.bin") % generateRandomString(9));
	std::ofstream luabinary(binary, std::ios::out | std::ios::binary);
	luabinary.write(lobj->s, lobj->size);
	luabinary.close();

	//WRITE << std::string(chunkname) << NL;
}