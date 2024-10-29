#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "modifiers.hpp"

enum e_resource_type {
	WOOD = 0,
	STONE = 1,
	COUNT = 2 // Always last to keep track of the number of resources
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
