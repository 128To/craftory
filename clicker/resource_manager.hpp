#pragma once

// This object is primarly made to capture the progression of the player through the game with a vectorized data structure for the resources holding.

//TOSTUDY: Possibility of a n-linked list OR n-ary reversed tree for data structure for tech tree representation with an abstraction layer for unlocking condition analysis.
//REFUTED: The possibility has been exploited in the techtree.hpp file, no linked-list, only hashmaps for data manipulation
// Because 128To value more the space complexity in this type of project instead of time complexity.
#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>

#include "resource.hpp"

class resource_manager {
public:
	static resource_manager& get_instance() {
		static resource_manager instance;
		return instance;
	}

	template<enum e_resource_type T_>
	resource<T_>& get_resource() { //to add and get resources to fetch.
		if (!m_resources[T_])
			m_resources[T_] = std::make_unique<resource<T_>>();
		return *static_cast<resource<T_>*>(m_resources[T_].get());
	}

	std::unordered_map<e_resource_type, std::unique_ptr<i_resource> > m_resources;
};