#pragma once

#include <algorithm>
#include <cstdint>
#include <chrono>
#include <thread>
#include <string>

#include "resource_manager.hpp"
#include "building_manager.hpp"

#define IDLE_TICK_RATE 1

class game {
public:
	static uint64_t gold_counter;
	static uint64_t gps_upgrade_cost;
	static uint64_t click_value_upgrade_cost;
	uint32_t click_value;
	uint64_t gold_per_second;
	resource_manager m_resources;
	factory_manager m_factories;
public:
	game() : click_value(1), gold_per_second(0) {}

	void gold_click(void) { this->gold_counter += this->click_value; }
	void gps_click() { 
		if (!this->can_buy_upgrade(gps_upgrade_cost))
			return;
		this->gold_counter -= gps_upgrade_cost;
		this->gold_per_second++;
	}
	void cv_click() {
		if (!this->can_buy_upgrade(click_value_upgrade_cost))
			return;
		this->gold_counter -= click_value_upgrade_cost;
		this->click_value++;
	}

	template<enum e_resource_type _T, enum e_resource_type... Rest>
	void build_factory() {
		if (!this->can_buy_upgrade(m_factories.get_factory< _T, Rest...>().factory_cost))
			return;
		this->gold_counter -= m_factories.get_factory<_T, Rest...>().factory_cost;
		m_factories.get_factory<_T, Rest...>().update_factory_count();
	}

	void update_gold_bgps() {
		std::thread idle_thread([&]() {
			while (true) {
				std::this_thread::sleep_for(std::chrono::seconds(IDLE_TICK_RATE));
				gold_counter += gold_per_second;
			}
			});
		idle_thread.detach();
	}

	template <enum e_resource_type _T, enum e_resource_type... Rest>
	void yield_factory_resources() {
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
	bool can_buy_upgrade(uint64_t upgrade_cost) {
		return this->gold_counter >= upgrade_cost;
	}
};