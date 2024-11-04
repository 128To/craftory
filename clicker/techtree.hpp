#pragma once

#include <algorithm>
#include <cstdint>
#include <chrono>
#include <thread>

#include "resource_manager.hpp"
#include "building_manager.hpp"

class game;

class techtree {
public:
	uint16_t unlocked_resources;
};