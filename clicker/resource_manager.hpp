#pragma once

#include <cstdint>
#include <string>
#include <vector>

//TODO: Add source control to the modifier to identify where the modifier is coming from (e.g. building, upgrade, etc.)
class modifier {
public:
	double multiplier;
	double additive;

	modifier(double multiplier, double additive) : multiplier(multiplier), additive(additive) {}
	modifier(double multiplier) : modifier(multiplier, 0.0) {}
	modifier(double additive) : modifier(1.0, additive) {}
	modifier() : modifier(1.0, 0.0) {}
};

class resource {
public:
	std::string name;
	uint64_t generation_rate;
	uint64_t amount;
	std::vector<modifier> modifiers;
public:
	resource(const std::string& name, const uint64_t& generation_rate, const uint64_t& initial_amount)
		: name(name), generation_rate(generation_rate), amount(initial_amount) {}
	resource(const std::string& name, const uint64_t& generation_rate)
		: resource(name, generation_rate, 0) {}
};

class resource_manager {
public:
	std::vector<resource> resources;
public:
	resource_manager() {}
	resource_manager(const std::vector<resource>& resources) : resources(resources) {}
	resource_manager(const std::initializer_list<resource>& resources) : resources(resources) {}
};