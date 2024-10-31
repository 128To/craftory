#pragma once

#include <cmath>
#include <cstdint>

#include "resource_type.hpp"

#define BASE_BUILDING_COUNT 0
#define BASE_BUILDING_PRODUCTION 1
#define BASE_BUILDING_COST 20

uint64_t BASE_BUILDING_COST_(uint32_t tier_era) {
	return BASE_BUILDING_COST * static_cast<uint64_t>(std::round(std::pow(2, tier_era)));
}

class i_base_factory {
public:
	virtual ~i_base_factory() = default;
	virtual uint16_t get_factory_count() = 0;
};

// Singleton implementation with static count instead of singling object to avoid high memory usage
template<enum e_resource_type T_>
class base_factory : public i_base_factory {
	// Each factory represents a different resource type that can be produced, you can have multiple factories of the same type but the cost and production will be different
	// The incrementation of the factory count is done in the constructor because when instantiating a factory, the factory is built. But if the factory is destroyed, the count is not decremented
	// Because as each instance of the factory represents a unique resource type, the count isn't static. If factory count = 0, then there are no factories of that type.
private:
	const uint8_t base_factory_production;
	const uint64_t base_factory_cost;
public:
	uint16_t factory_count;
	uint64_t factory_cost;
	uint64_t factory_production;
public:
	base_factory() : base_factory_production(BASE_BUILDING_PRODUCTION), base_factory_cost(BASE_BUILDING_COST_(static_cast<uint32_t>(T_))), factory_count(BASE_BUILDING_COUNT) {
		factory_cost = base_factory_cost;
		factory_production = base_factory_production;
	}
	uint16_t get_factory_count() override { return factory_count; }
	uint16_t update_factory_count() { return ++factory_count; }
};