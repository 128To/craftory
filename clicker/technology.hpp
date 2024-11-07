#pragma once

#include <unordered_map>
#include <array> 

#include "building.hpp"

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

struct technology_cost {
	e_technology_type type;
	uint64_t gold_cost;
	std::unordered_map<e_resource_type, uint64_t> resource_costs;
};

struct unlocked_resources {
	e_technology_type type;
	std::vector<e_resource_type> resources;
};

struct unlocked_resources {
	e_technology_type type;
	std::vector<e_technology_type> technologies;
};

// Technology cost in gold and resources
std::array<technology_cost, e_technology_type::COUNT> technology_data = { {
	{e_technology_type::SAWMILL, 100, {{e_resource_type::WOOD, 50}}},
	{e_technology_type::CARRIER, 150, {{e_resource_type::WOOD, 75}}},
	{e_technology_type::BASIC_MINE, 200, {{e_resource_type::STONE, 100}}},

	{e_technology_type::ADVANCED_MINE, 300, {{e_resource_type::STONE, 150}}},
	{e_technology_type::REFINEMENT, 400, {{e_resource_type::COAL, 200}}},
	{e_technology_type::OIL_DRILL, 500, {{e_resource_type::COAL, 250}}}
} };

// Resources unlocked by the technology
std::array<unlocked_resources, e_technology_type::COUNT> unlocked_resources_data = { {
	{e_technology_type::SAWMILL, {e_resource_type::WOOD}},
	{e_technology_type::CARRIER, {e_resource_type::STONE}},
	{e_technology_type::BASIC_MINE, {e_resource_type::COAL}},

	{e_technology_type::ADVANCED_MINE, {e_resource_type::IRON, e_resource_type::BAUXITE, e_resource_type::COPPER}},
	{e_technology_type::REFINEMENT, {e_resource_type::SILICA}},
	{e_technology_type::OIL_DRILL, {e_resource_type::OIL}}
} };

std::array<unlocked_technologies, e_technology_type::COUNT> unlocked_technologies_data = { {
	{e_technology_type::SAWMILL, {e_technology_type::CARRIER}},
	{e_technology_type::CARRIER, {e_technology_type::BASIC_MINE}},
	{e_technology_type::BASIC_MINE, {e_technology_type::ADVANCED_MINE}},

	{e_technology_type::ADVANCED_MINE, {e_technology_type::REFINEMENT}},
	{e_technology_type::REFINEMENT, {e_technology_type::OIL_DRILL}},
	{e_technology_type::OIL_DRILL, {}}
} };

inline const std::string& get_technology_name(e_technology_type tech) {
	return technology_type_names[technology_data[tech].type];
}
inline uint64_t get_technology_gold_cost(e_technology_type tech) {
	return technology_data[tech].gold_cost;
}
inline const std::unordered_map<e_resource_type, uint64_t>& get_technology_resource_costs(e_technology_type tech) {
	return technology_data[tech].resource_costs;
}
inline const std::vector<e_resource_type>& get_unlocked_resources(e_technology_type tech) {
	return unlocked_resources_data[tech].resources;
}