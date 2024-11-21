#pragma once

// The resources are made to craft multiple tools, automations machines but can be sold for gold.
// It can also be used, at a certain state of the minigame, for scientific research and for global export.

#include <cstdint>
#include <string>
#include <vector>

#include "building.hpp"

class i_resource {
public:
	virtual uint64_t get_generation_rate() const = 0;
	virtual uint64_t get_amount() const = 0;
};

template<e_resource_type T_>
class resource : public i_resource {
public:
	e_resource_type resource_type;
	uint64_t amount;
private:
	uint64_t generation_rate;
public:
	resource() : resource_type(T_), generation_rate(0), amount(0) {}
	uint64_t get_generation_rate() const override { return generation_rate; }
	uint64_t get_amount() const override { return amount; }
};
