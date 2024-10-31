#pragma once

#include <algorithm>
#include <cstdint>
#include <chrono>
#include <thread>
#include <string>

#include "resource_manager.hpp"
#include "building.hpp"

#define IDLE_TICK_RATE 1 // Generation rate is in seconds

class game {
public:
	static uint64_t gold_counter;
	static uint64_t gps_upgrade_cost;
	static uint64_t click_value_upgrade_cost;
	uint32_t click_value;
	uint64_t gold_per_second;
	resource_manager m_resources;
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

	void update_gold_bgps() {
		std::thread idle_thread([&]() {
			while (true) {
				std::this_thread::sleep_for(std::chrono::seconds(IDLE_TICK_RATE));
				gold_counter += gold_per_second;
			}
			});
		idle_thread.detach();
	}

	void update_resources() {
		std::thread idleThread([&]() {
			while (true) {
				std::this_thread::sleep_for(std::chrono::seconds(IDLE_TICK_RATE));
				std::for_each(m_resources.resources.begin(), m_resources.resources.end(), [&](resource& res) {
					res.amount += res.generation_rate;
					std::for_each(res.modifiers.begin(), res.modifiers.end(), [&](modifier& mod) {
						res.amount *= mod.multiplier;
						res.amount += mod.additive;
						});
					}
				);
			}
			});
		idleThread.detach();
	}
private:
	bool can_buy_upgrade(uint64_t upgrade_cost) {
		return this->gold_counter >= upgrade_cost;
	}
};