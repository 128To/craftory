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
	uint32_t click_value;
	resource_manager m_resources;
public:
	game() : click_value(1) {}
	game(const uint32_t& click_value) : click_value(click_value) {}
	game(const resource_manager& resources) : m_resources(resources), click_value(1) {}
	game(const uint32_t& click_value, const resource_manager& resources) : click_value(click_value), m_resources(resources) {}

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