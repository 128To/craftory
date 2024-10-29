#pragma once

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