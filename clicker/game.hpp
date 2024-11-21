#pragma once

#include <algorithm>
#include <cstdint>
#include <ctype.h>
#include <chrono>
#include <thread>
#include <string>

#include "resource_manager.hpp"
#include "building_manager.hpp"
#include "techtree.hpp"

constexpr uint8_t IDLE_TICK_RATE = 1;
constexpr float_t BASE_UPGRADE_COST_INC = 1.15f;

class game {
public:
	static uint64_t gold_counter;
	static uint64_t gps_upgrade_cost;
	static uint64_t click_value_upgrade_cost;
	uint32_t click_value;
	uint64_t gold_per_second;
	resource_manager m_resources;
	factory_manager m_factories;
	techtree m_techtree;
public:
	game() : click_value(1), gold_per_second(0) {}

	inline void gold_click(void) noexcept { this->gold_counter += this->click_value; }
	inline void gps_click() { 
		if (!this->can_buy_upgrade(gps_upgrade_cost))
			return;
		this->gold_counter -= gps_upgrade_cost; 
		gps_upgrade_cost = static_cast<uint64_t>(gps_upgrade_cost * BASE_UPGRADE_COST_INC);
		this->gold_per_second++;
	}
	inline void cv_click() {
		if (!this->can_buy_upgrade(click_value_upgrade_cost))
			return;
		this->gold_counter -= click_value_upgrade_cost;
		click_value_upgrade_cost = static_cast<uint64_t>(click_value_upgrade_cost * BASE_UPGRADE_COST_INC);
		this->click_value++;
	}

	template<enum e_resource_type _T, enum e_resource_type... Rest>
	inline void build_factory() {
		if (!this->can_buy_upgrade(m_factories.get_factory< _T, Rest...>().factory_cost))
			return;
		this->gold_counter -= m_factories.get_factory<_T, Rest...>().factory_cost;
		this->m_factories.get_factory<_T, Rest...>().factory_cost = static_cast<uint64_t>(m_factories.get_factory<_T, Rest...>().factory_cost * BASE_UPGRADE_COST_INC);
		m_factories.get_factory<_T, Rest...>().update_factory_count();
	}

	inline void update_gold_bgps() {
		std::thread idle_thread([&]() {
			while (true) {
				std::this_thread::sleep_for(std::chrono::seconds(IDLE_TICK_RATE));
				gold_counter += gold_per_second;
			}
			});
		idle_thread.detach();
	}

	template <enum e_resource_type _T, enum e_resource_type... Rest>
	inline void yield_factory_resources() {
		std::thread idle_thread([&]() {
			while (true) {
				std::this_thread::sleep_for(std::chrono::seconds(IDLE_TICK_RATE));
				this->m_resources.get_resource<_T>().amount +=
					this->m_factories.get_factory<_T, Rest...>().factory_count * 
					this->m_factories.get_factory<_T, Rest...>().factory_production;  
			
				(void(std::initializer_list<int>{
					(this->m_resources.get_resource<Rest>().amount +=
						this->m_factories.get_factory<_T, Rest...>().factory_count*
						this->m_factories.get_factory<_T, Rest...>().factory_production, 0)...}));
			}
			});
		idle_thread.detach();
	}
private:
	inline const bool can_buy_upgrade(uint64_t& upgrade_cost) noexcept {
		return this->gold_counter >= upgrade_cost;
	}

	// Game to Techtree interaction
	//TODO : Separates this into a dedicated class
	//TODO : Create interfaces for the dedicated class for better architecture
	inline const bool can_be_resources_purshased(const e_technology_type& type_) noexcept {
		const auto& resource_costs = this->m_techtree.m_technologies.at(type_).get()->m_resources_cost;
		for (const auto& [resource_type, cost] : resource_costs) {
			if (this->m_resources.m_resources.at(resource_type)->get_amount() < cost) {
				return false;
			}
		}
		return true;
	}

	inline const bool can_be_purshased(const e_technology_type& type_, const uint64_t& current_game_gold_counter_) noexcept {
		bool cbp_gold = current_game_gold_counter_ >= this->m_techtree.m_technologies.at(type_).get()->m_gold_cost;
		bool cbp_resources = can_be_resources_purshased(type_);
		return cbp_gold && cbp_resources;
	}

	inline const bool dependencies_are_unlocked(const e_technology_type& type_) const noexcept {
		std::for_each(	this->m_techtree.m_technologies.at(type_).get()->m_dependencies.begin(),
						this->m_techtree.m_technologies.at(type_).get()->m_dependencies.end(), 
			[&](const enum e_technology_type& _dep) {
				if (!this->m_techtree.m_technologies.at(_dep).get()->is_unlocked) return false;
			});
		return true;
	}

	inline const bool can_be_unlocked(const e_technology_type& type_, const uint64_t& current_game_gold_counter_) noexcept {
		return dependencies_are_unlocked(type_) && can_be_purshased(type_, current_game_gold_counter_);
	}
};