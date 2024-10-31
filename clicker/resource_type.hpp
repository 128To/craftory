#pragma once

#include <unordered_map>

enum e_resource_type {
	WOOD = 0,
	STONE = 1,
	COAL = 2,
	// Automatic number allocation for the count done by the compiler
	COUNT // Always last to keep track of the number of resources
};

std::unordered_map<e_resource_type, std::string> resource_type_names = {
	{e_resource_type::WOOD, "Wood Factory"},
	{e_resource_type::STONE, "Stone Factory"},
	{e_resource_type::COAL, "Coal Factory"}
	// ...
};