#pragma once

#include <vector>
#include <utility>
#include <memory>
#include <unordered_map>
#include <string>

#include "resource.hpp"

class factory_manager {
public:
	static factory_manager& get_instance() {
		static factory_manager instance;
		return instance;
	}

	template<enum e_resource_type T_>
	base_factory<T_>& get_factory() {
		if (!m_factories.contains(T_))
			m_factories[T_] = std::make_unique<base_factory<T_>>();
		return *static_cast<base_factory<T_>*>(m_factories[T_].get());
	}
private:
	std::unordered_map<enum e_resource_type, std::unique_ptr<i_base_factory>> m_factories;
	
	std::string get_type_name(e_resource_type type) const noexcept {
		switch (type) {
		case e_resource_type::WOOD: return "Wood Factory";
		case e_resource_type::STONE: return "Stone Factory";
		default: return "Unknown";
		}
	}
};