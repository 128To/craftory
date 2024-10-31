#pragma once

// This object is primarly made to capture the progression of the player through the game with a vectorized data structure for the resources holding.

//TOSTUDY: Possibility of a n-linked list OR n-ary reversed tree for data structure for tech tree representation with an abstraction layer for unlocking condition analysis.

#include <cstdint>
#include <string>
#include <vector>

#include "resource.hpp"

class resource_manager {
public:
	std::vector<resource> resources;
public:
	resource_manager() {}
	resource_manager(const std::vector<resource>& resources) : resources(resources) {}
	resource_manager(const std::initializer_list<resource>& resources) : resources(resources) {}
};