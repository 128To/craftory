#pragma once

#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>


#include <thread>
#include <chrono>
#include <memory>
#include <atomic>
#include <functional>

#include "game.hpp"

class GameUI { 
public:
    GameUI(std::unique_ptr<game> game) : game_(std::move(game)), fm_(nana::API::make_center(500, 200)) {
        fm_.caption("Clicker");

        nana::place layout(fm_);
        layout.div("<vert margin=10 gap=10 labels><vert margin=10 gap=10 buttons><vert margin=10 gap=10 upgrades><vert margin=10 gap=10 building> <vert margin=10 gap=10 resources>");

        gold_label_ = std::make_unique<nana::label>(fm_);
        gps_label_ = std::make_unique<nana::label>(fm_);
        layout["labels"] << *gold_label_;
        layout["labels"] << *gps_label_;

        click_button_ = std::make_unique<nana::button>(fm_);
        click_button_->caption("Click me!");
        layout["buttons"] << *click_button_;

        // --- Upgrades Section ---
        // ---------- Gold Per Second ----------
        gps_upgrade_button_ = std::make_unique<nana::button>(fm_);
        gps_upgrade_button_->caption("Upgrade GPS");
        layout["upgrades"] << *gps_upgrade_button_;

        gps_upgrade_cost_label_ = std::make_unique<nana::label>(fm_);
        layout["upgrades"] << *gps_upgrade_button_;

        // ---------- Click Value ----------
        click_value_upgrade_button_ = std::make_unique<nana::button>(fm_);
        click_value_upgrade_button_->caption("Upgrade Click Value");
        layout["upgrades"] << *click_value_upgrade_button_;

        click_value_upgrade_label_ = std::make_unique<nana::label>(fm_);
        layout["upgrades"] << *click_value_upgrade_label_;

        // --- Building section ---
		building_button_ = std::make_unique<nana::button>(fm_);
		building_button_->caption("Build Factory");
		layout["building"] << *building_button_;

		building_label_ = std::make_unique<nana::label>(fm_);
		building_cost_label_ = std::make_unique<nana::label>(fm_);
		layout["building"] << *building_label_;
		layout["building"] << *building_cost_label_;     

		// --- Resources Section ---
		resources_label_ = std::make_unique<nana::label>(fm_);
		layout["resources"] << *resources_label_;

        layout.collocate();

        this->update_labels_thr();
        game_->update_gold_bgps();
		game_->yield_factory_resources<e_resource_type::WOOD>();

        bind_click_event(*click_button_, [this]() { game_->gold_click(); });
        bind_click_event(*gps_upgrade_button_, [this]() { game_->gps_click(); });
        bind_click_event(*click_value_upgrade_button_, [this]() { game_->cv_click(); });
		bind_click_event(*building_button_, [this]() { game_->build_factory<e_resource_type::WOOD>(); });

        fm_.show();
    }
private:
    void update_labels() {
        gold_label_->caption(std::to_string(game_->gold_counter) + " golds");
        gps_label_->caption(std::to_string(game_->gold_per_second) + " per second");
        // Update sections
        gps_upgrade_cost_label_->caption("Upgrade gold per second: " + std::to_string(game_->gps_upgrade_cost));
        click_value_upgrade_label_->caption("Upgrade click value: " + std::to_string(game_->click_value_upgrade_cost));
    }

    void update_resources_labels() {
		building_label_->caption("Wood Factory: " + std::to_string(game_->m_factories.get_factory<e_resource_type::WOOD>().factory_count));
		building_cost_label_->caption("Cost: " + std::to_string(game_->m_factories.get_factory<e_resource_type::WOOD>().factory_cost));
		resources_label_->caption("Wood: " + std::to_string(game_->m_resources.get_resource<e_resource_type::WOOD>().amount));
    }

    template <typename func>
    void bind_click_event(nana::button& button, func&& action) {
        button.events().click([this, action]() {
            action();
            update_labels();
            update_resources_labels();
        });
    }

    void update_labels_thr() {
        std::thread updateThread([this]() {
            while (true) {
                update_labels();
                update_resources_labels();
                std::this_thread::sleep_for(std::chrono::milliseconds(IDLE_TICK_RATE));
            }
            });
        updateThread.detach();
    }

    std::unique_ptr<game> game_;
    nana::form fm_;
    std::unique_ptr<nana::label> gold_label_;
    std::unique_ptr<nana::label> gps_label_;

    // --- Upgrades Section ---
    // ---------- Gold Per Second ----------
    std::unique_ptr<nana::button> click_button_;
    std::unique_ptr<nana::button> gps_upgrade_button_;
    std::unique_ptr<nana::label> gps_upgrade_cost_label_;

    // ---------- Click Value ----------
    std::unique_ptr<nana::button> click_value_upgrade_button_;
    std::unique_ptr<nana::label> click_value_upgrade_label_;

    // --- Building Section ---
	std::unique_ptr<nana::label> building_label_;
	std::unique_ptr<nana::button> building_button_;
	std::unique_ptr<nana::label> building_cost_label_;

	// --- Resources Section ---
	std::unique_ptr<nana::label> resources_label_;
};
