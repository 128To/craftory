#pragma once

#include <algorithm>
#include <cstdint>
#include <chrono>
#include <thread>
#include <string>

#include "resource_manager.hpp"

#define IDLE_TICK_RATE 1 // Generation rate is in seconds

class game {
public:
	static uint64_t gold_counter;
	static uint64_t gps_upgrade_cost;
	uint32_t click_value;
	uint64_t gold_per_second;
	resource_manager m_resources;
public:
	game() : click_value(1), gold_per_second(0) {}

	std::string click() {
		gold_counter += click_value;
		return std::to_string(gold_counter);
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
};