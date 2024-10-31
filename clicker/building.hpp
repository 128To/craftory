#pragma once

#include <cmath>
#include <cstdint>

#include "resource.hpp"

#define BASE_BUILDING_PRODUCTION 1
#define BASE_BUILDING_COST 100000

uint32_t BASE_BUILDING_COST_(uint32_t tier_era) {
	return BASE_BUILDING_COST * std::pow(2, tier_era);
}

// Singleton implementation with static count instead of singling object to avoid high memory usage
// TODO: Singleton
class wood_factory {
private:
	static uint16_t wood_factory_count;
	const uint8_t wood_factory_base_production;
	const uint32_t wood_factory_base_cost;
public:
	uint64_t wood_factory_cost;
	uint64_t wood_factory_production;

public: 
	wood_factory() : wood_factory_base_production(1), wood_factory_base_cost(BASE_BUILDING_COST_(static_cast<uint32_t>(e_resource_type::WOOD))) {
		wood_factory_count++;
		wood_factory_cost = wood_factory_base_cost;
		wood_factory_production = wood_factory_base_production;
	}

	~wood_factory() {
		wood_factory_count--;
	}

	static uint16_t get_wood_factory_count() {
		return wood_factory_count;
	}
};

template<typename resource_type>
class base_factory {
	uint16_t factory_count;
	const uint8_t wood_factory_base_production;
	const uint32_t wood_factory_base_cost;
public:
	uint64_t wood_factory_cost;
	uint64_t wood_factory_production;

};