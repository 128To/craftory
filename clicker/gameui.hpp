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
    GameUI(std::unique_ptr<game> game) : game_(std::move(game)), fm_() {
        fm_.caption("Clicker");

        nana::place layout(fm_);
        layout.div("<vert margin=10 gap=10 <weight=30><weight=20% labels> <weight=40% buttons> <weight=30% upgrades>");

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
        wood_factory_button_ = std::make_unique<nana::button>(fm_);
        wood_factory_button_->caption("Buy a wood_factory");
        layout["building"] << *wood_factory_button_;

        wood_factory_label_ = std::make_unique<nana::label>(fm_);
        layout["building"] << *wood_factory_label_;

        layout.collocate();

        this->update_labels_thr();
        game_->update_gold_bgps();

        bind_click_event(*click_button_, [this]() { game_->gold_click(); });
        bind_click_event(*gps_upgrade_button_, [this]() { game_->gps_click(); });
        bind_click_event(*click_value_upgrade_button_, [this]() { game_->cv_click(); });

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
        wood_factory_label_->caption(std::to_string(game_->wood_factory) + "")
    }

    template <typename func>
    void bind_click_event(nana::button& button, func&& action) {
        button.events().click([this, action]() {
            action();
            update_labels();
        });
    }

    void update_labels_thr() {
        std::thread updateThread([this]() {
            while (true) {
                update_labels();
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
    std::unique_ptr <nana::button> wood_factory_button_;
    std::unique_ptr<nana::label> wood_factory_label_;
};
