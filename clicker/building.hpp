#pragma once

#include <cmath>
#include <cstdint>
#include <unordered_map> 
#include <initializer_list> 

#include "resource_type.hpp"

constexpr uint8_t BASE_BUILDING_COUNT = 0;
constexpr uint8_t BASE_BUILDING_PRODUCTION = 1;
constexpr uint8_t BASE_BUILDING_COST = 20;

uint64_t BASE_BUILDING_COST_(uint32_t tier_era) {
    return BASE_BUILDING_COST * static_cast<uint64_t>(std::round(std::pow(2, tier_era)));
}

class i_base_factory {
public:
    virtual ~i_base_factory() = default;
    virtual void update_factory_count() = 0;
    virtual uint16_t get_factory_count() = 0;
};

template <enum e_resource_type _T, e_resource_type... Resources>
class base_factory : public i_base_factory {
public:
    const uint8_t factory_production;       // Production rate shared by all resources of the same factory
    uint64_t factory_cost;            // Cost shared by all resources of the same factory
    uint16_t factory_count;

public:
    base_factory()
        : factory_production(BASE_BUILDING_PRODUCTION),
		factory_cost(BASE_BUILDING_COST_(static_cast<uint32_t>(_T))),
          factory_count(BASE_BUILDING_COUNT) {}

    void update_factory_count() override { ++factory_count; }

    uint16_t get_factory_count() override { return factory_count; }
    uint8_t get_production_rate() const noexcept { return factory_production * factory_count; }
    uint64_t get_cost() const noexcept { return factory_cost; }
};
