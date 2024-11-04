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

    template<e_resource_type T_>
    base_factory<T_>& get_factory() {
        return get_factory_impl<T_>();
    }

    template<e_resource_type T_, e_resource_type... Rest>
    typename std::enable_if<(sizeof...(Rest) > 0), base_factory<T_>&>::type
        get_factory() {
        std::vector<e_resource_type> types = { T_, Rest... };
        for (const auto& type : types)
            get_factory_impl<type>();
        return *static_cast<base_factory<T_>*>(m_factories[types[0]].get());
    }

private:
    template<e_resource_type T_>
    base_factory<T_>& get_factory_impl() {
        if (!m_factories.contains(T_))
            m_factories[T_] = std::make_unique<base_factory<T_>>();
        return *static_cast<base_factory<T_>*>(m_factories[T_].get());
    }

    std::unordered_map<e_resource_type, std::unique_ptr<i_base_factory>> m_factories;

    std::string get_type_name(e_resource_type type) {
        auto it = resource_type_names.find(type);
        return (it != resource_type_names.end()) ? it->second : "Unknown Factory";
    }
};
