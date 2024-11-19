#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include <type_traits>

#include "resource.hpp"

class factory_manager {
public:
    static factory_manager& get_instance() {
        static factory_manager instance;
        return instance;
    }

    template<e_resource_type T_>
    inline base_factory<T_>& get_factory() noexcept {
        return get_factory_impl<T_>();
    }

    template<e_resource_type T_, e_resource_type... Rest>
	inline typename std::enable_if<sizeof...(Rest) != 0, base_factory<T_, Rest...>&>::type get_factory() noexcept {
		return get_factory_impl<T_, Rest...>();
	}

private:
    template<e_resource_type... Resources>
    inline base_factory<Resources...>& get_factory_impl() {
        std::string key = get_key<Resources...>();

        if (!m_factories.contains(key)) {
            m_factories[key] = std::make_unique<base_factory<Resources...>>();
        }

        return *static_cast<base_factory<Resources...>*>(m_factories[key].get());
    }

    template<e_resource_type... Resources>
    inline const std::string get_key() const noexcept {
        return ((std::to_string(static_cast<int>(Resources)) + "_") + ...);
    }

    std::unordered_map<std::string, std::unique_ptr<i_base_factory>> m_factories;

    inline const std::string get_type_name(e_resource_type& type) const noexcept {
        auto it = resource_type_names.find(type);
        return (it != resource_type_names.end()) ? it->second : "Unknown Factory";
    }
};
