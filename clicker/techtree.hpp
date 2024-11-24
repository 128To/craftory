#pragma once

#include <algorithm>
#include <cstdint>
#include <chrono>
#include <thread>
#include <iostream> // TEST

#include "technology.hpp"

class game;

class techtree {
public:
	techtree() {
		for (uint8_t i{}; i < static_cast<uint8_t>(e_technology_type::COUNT); ++i) {
			auto _type = static_cast<e_technology_type>(i);
			this->m_technologies[_type] = std::make_unique<technology>(_type);
		}
	}
public:
	std::unordered_map<e_technology_type, std::unique_ptr<technology>> m_technologies;
};