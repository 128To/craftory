#pragma once

#include <unordered_map>
#include <vector>
#include <memory>
#include <string>

#include "building.hpp"
#include "technology_data_repository.hpp"

class technology {
public:
    explicit technology(e_technology_type& type)
        : m_type(type),
        m_gold_cost(technology_data_repository::get_technology_cost(type).gold_cost),
        m_resources_cost(technology_data_repository::get_technology_cost(type).resource_costs),
        m_resources(technology_data_repository::get_technology_resources(type).unlocked_resources),
        m_dependencies(technology_data_repository::get_technology_dependencies(type).required_technologies),
        m_name(technology_data_repository::get_technology_name(type)),
        is_unlocked(false) {
    }

    const e_technology_type m_type;                  // Type of the technology
    const uint64_t m_gold_cost;                      // Gold cost of the technology
    const std::unordered_map<e_resource_type, uint64_t> m_resources_cost; // Resources cost of the technology
    const std::vector<e_resource_type>& m_resources; // Resources unlocked by the technology
    const std::vector<e_technology_type>& m_dependencies; // Technologies unlocking condition
    const std::string& m_name;                       // Name of the technology
    bool is_unlocked;                                // Unlock status

private:
    static std::unordered_map<e_technology_type, std::shared_ptr<technology>> technology_instances;
};
