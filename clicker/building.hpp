#pragma once

#include <cmath>
#include <cstdint>
#include <unordered_map> // Added for unordered_map
#include <initializer_list> // Added for initializer_list

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
    virtual void update_factory_count() = 0;
    virtual uint16_t get_factory_count() = 0;
};

template <e_resource_type... Resources>
class base_factory : public i_base_factory {
public:
    const uint8_t factory_production;       // Production rate shared by all resources of the same factory
    const uint64_t factory_cost;            // Cost shared by all resources of the same factory
    uint16_t factory_count;

public:
    base_factory()
        : factory_production(BASE_BUILDING_PRODUCTION),
          factory_cost(BASE_BUILDING_COST_(std::min({ static_cast<uint32_t>(Resources)... }))), // Use sizeof... to get the number of resources
          factory_count(BASE_BUILDING_COUNT) {}

    void update_factory_count() override { ++factory_count; }

    uint16_t get_factory_count() override { return factory_count; }
    uint8_t get_production_rate() const { return factory_production * factory_count; }
    uint64_t get_cost() const { return factory_cost; }

    std::unordered_map<e_resource_type, uint64_t> produce() const {
        std::unordered_map<e_resource_type, uint64_t> produced_resources;
        (produced_resources.emplace(Resources, factory_production * factory_count), ...);
        return produced_resources;
    }
};
