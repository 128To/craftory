#pragma once

// The resources are made to craft multiple tools, automations machines but can be sold for gold.
// It can also be used, at a certain state of the minigame, for scientific research and for global export.

#include <cstdint>
#include <string>
#include <vector>

#include "modifiers.hpp"

enum e_resource_type {
	WOOD = 0,
	STONE = 1,
	COAL = 2,
	// Automatic number allocation for the count done by the compiler
	COUNT // Always last to keep track of the number of resources
};

class resource {
public:
	e_resource_type resource_type;
	uint64_t generation_rate;
	uint64_t amount;
	std::vector<modifier> modifiers;
public:
	resource(const e_resource_type& resource_type, const uint64_t& generation_rate, const uint64_t& initial_amount)
		: resource_type(resource_type), generation_rate(generation_rate), amount(initial_amount) {}
	resource(const e_resource_type& resource_type, const uint64_t& generation_rate)
		: resource(resource_type, generation_rate, 0) {}
};
