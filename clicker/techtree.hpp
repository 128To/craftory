#pragma once

#include <algorithm>
#include <cstdint>
#include <chrono>
#include <thread>

#include "technology.hpp"

class game;

class techtree {
public:
	uint16_t unlocked_resources;
};