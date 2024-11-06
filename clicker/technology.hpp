#pragma once

#include <unordered_map>

#include "building_manager.hpp"

enum e_technology_type {
	SAWMILL, 
	CARRIER,
	BASIC_MINE,
	
	ADVANCED_MINE,
	REFINEMENT,
	OIL_DRILL,

	// Automatic number allocation for the count done by the compiler
	COUNT // Always last to keep track of the number of technologies
};

std::unordered_map<e_technology_type, std::string> technology_type_names = {
	{e_technology_type::SAWMILL, "Sawmill"},
	{e_technology_type::CARRIER, "Carrier"},
	{e_technology_type::BASIC_MINE, "Basic Mine"},
	{e_technology_type::ADVANCED_MINE, "Advanced Mine"},
	{e_technology_type::REFINEMENT, "Refinement"},
	{e_technology_type::OIL_DRILL, "Oil Drill"}
	// ...
};