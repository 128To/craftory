#pragma once

#include "building.hpp"

#include <string>
#include <unordered_map>


enum class e_technology_type {
    SAWMILL,
    CARRIER,
    BASIC_MINE,
    ADVANCED_MINE,
    REFINEMENT,
    OIL_DRILL,
    COUNT // Used for array sizing
};

struct technology_cost {
    uint64_t gold_cost;
    std::unordered_map<e_resource_type, uint64_t> resource_costs;
};

struct technology_resources {
    std::vector<e_resource_type> unlocked_resources;
};

struct technology_dependencies {
    std::vector<e_technology_type> required_technologies;
};

// Data Repository
class technology_data_repository {
public:
    inline static const technology_cost& get_technology_cost(const e_technology_type& type) noexcept;
    inline static const technology_resources& get_technology_resources(const e_technology_type& type) noexcept;
    inline static const technology_dependencies& get_technology_dependencies(const e_technology_type& type) noexcept;
    inline static const std::string& get_technology_name(const e_technology_type& type) noexcept;

private:
    static const std::unordered_map<e_technology_type, technology_cost> costs;
    static const std::unordered_map<e_technology_type, technology_resources> resources;
    static const std::unordered_map<e_technology_type, technology_dependencies> dependencies;
    static const std::unordered_map<e_technology_type, std::string> names;
};

const std::unordered_map<e_technology_type, technology_cost> technology_data_repository::costs = {
    {e_technology_type::SAWMILL, {100, {}}},
    {e_technology_type::CARRIER, {1500, {{e_resource_type::WOOD, 75}}}},
    {e_technology_type::BASIC_MINE, {12000, {{e_resource_type::STONE, 100}, {e_resource_type::WOOD, 400}}}},
    {e_technology_type::ADVANCED_MINE, {300, {{e_resource_type::STONE, 150}}}},
    {e_technology_type::REFINEMENT, {400, {{e_resource_type::COAL, 200}}}},
    {e_technology_type::OIL_DRILL, {500, {{e_resource_type::COAL, 250}}}}
};

const std::unordered_map<e_technology_type, technology_resources> technology_data_repository::resources = {
    {e_technology_type::SAWMILL, {{e_resource_type::WOOD}}},
    {e_technology_type::CARRIER, {{e_resource_type::STONE}}},
    {e_technology_type::BASIC_MINE, {{e_resource_type::COAL}}},
    {e_technology_type::ADVANCED_MINE, {{e_resource_type::IRON, e_resource_type::BAUXITE, e_resource_type::COPPER}}},
    {e_technology_type::REFINEMENT, {{e_resource_type::SILICA}}},
    {e_technology_type::OIL_DRILL, {{e_resource_type::OIL}}}
};

const std::unordered_map<e_technology_type, technology_dependencies> technology_data_repository::dependencies = {
    {e_technology_type::SAWMILL, {{}}},
    {e_technology_type::CARRIER, {{}}},
    {e_technology_type::BASIC_MINE, {{e_technology_type::SAWMILL, e_technology_type::CARRIER}}},
    {e_technology_type::ADVANCED_MINE, {{e_technology_type::BASIC_MINE}}},
    {e_technology_type::REFINEMENT, {{}}},
    {e_technology_type::OIL_DRILL, {{e_technology_type::REFINEMENT}}}
};

const std::unordered_map<e_technology_type, std::string> technology_data_repository::names = {
    {e_technology_type::SAWMILL, "Sawmill"},
    {e_technology_type::CARRIER, "Carrier"},
    {e_technology_type::BASIC_MINE, "Basic Mine"},
    {e_technology_type::ADVANCED_MINE, "Advanced Mine"},
    {e_technology_type::REFINEMENT, "Refinement"},
    {e_technology_type::OIL_DRILL, "Oil Drill"}
};

inline const std::string& technology_data_repository::get_technology_name(const e_technology_type& type_) noexcept {
    return names.at(type_);
}

inline const technology_cost& technology_data_repository::get_technology_cost(const e_technology_type& type_) noexcept {
    return costs.at(type_);
}
inline const technology_resources& technology_data_repository::get_technology_resources(const e_technology_type& type_) noexcept {
    return resources.at(type_);
}

inline const technology_dependencies& technology_data_repository::get_technology_dependencies(const e_technology_type& type_) noexcept {
    return dependencies.at(type_);
}
