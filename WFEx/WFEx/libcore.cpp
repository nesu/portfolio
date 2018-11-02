/*
*
* WFEx - Warframe script engine extention made for
* simulating player behaviour, extending UI and/or
* manipulating in-game objects.
*
*/

#include "libcore.h"
#include "darthton.h"

#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"


std::vector<std::shared_ptr<METINF>> Libcore::Methods;

std::shared_ptr<LIBINF>		Libcore::lib_Information;
std::shared_ptr<GMINF>		Libcore::gm_Information;

/* Value preserved at newthread detoured re-declaration. */
lua_State * Libcore::MasterState;

/* Seperate lua state for current module. */
lua_State * Libcore::LibState;

void Libcore::Initialize(const std::shared_ptr<LIBINF>& libi, const std::shared_ptr<GMINF>& gmi)
{
	/* Initializing empty variables */
	LibState = nullptr;
	MasterState = nullptr;

	/* Preserving game and current module information */
	lib_Information = libi;
	gm_Information = gmi;

	WRITE << "Libcore initialization finished." << NL;
	return;
}

/*	Method control function declarations	*/
void Libcore::Registry()
{
	WRITE << "Libcore::Registry started." << NL;
	using boost::property_tree::ptree;
	using boost::property_tree::read_json;
	using boost::property_tree::write_json;

	ptree property_tree;
	try
	{
		read_json(lib_Data "fn_registry.json", property_tree);
	}
	catch(boost::property_tree::json_parser_error ex)
	{
		WRITE << "Bad json file: " << ex.message() << NL;
		return;
	}

	for (auto & array_element : property_tree)
	{
		auto mtnf = std::make_shared<METINF>();

		mtnf->Label = array_element.second.get_child("Label").get_value<std::string>();
		mtnf->Pattern = array_element.second.get_child("Pattern").get_value<std::string>();
		mtnf->Mask = array_element.second.get_child("Mask").get_value<std::string>();
		FindPattern(mtnf);
		Methods.push_back(mtnf);
	}

	WRITE << "Libcore::Registry has ended with " << Methods.size() << " elements." << NL;
}

void Libcore::FindPattern(const std::shared_ptr<METINF>& metinf)
{
	auto _ddr = const_cast<LPVOID>(Search(static_cast<PBYTE>(gm_Information->Base()), gm_Information->Size(), reinterpret_cast<const uint8_t*>(metinf->GetBytes()), metinf->Mask.c_str()));
	if (_ddr == nullptr)
	{
		WRITE << "Signature scan failed to find " << metinf->Label << "." << NL;
		return;
	}

	metinf->Valid = TRUE;
	metinf->Address = _ddr;
	WRITE << "Function " << metinf->Label << " was found successfully (" << std::hex << metinf->Address << ")." << NL;
	return;
}

std::shared_ptr<METINF> Libcore::FindFunction(std::string label)
{
	auto it = std::find_if(Methods.begin(), Methods.end(), [&](std::shared_ptr<METINF> const& element)	{
		return element->Label == label;
	});

	if (it == Methods.end())
	{
		WRITE << "Given function (" << label << ") was not found." << NL;
		return nullptr;
	}

	return *it;
}