#pragma once

#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>


#include <thread>
#include <chrono>
#include <memory>
#include <atomic>
#include <functional>
#include <iostream>

#include "craftory_gui.h"
#include "game.hpp"

class GameUI {
public:
    GameUI(std::unique_ptr<game> game) : game_(std::move(game)) {
        nana::window wd;
        try {
            gui_ = std::make_unique<craftory_gui>(wd);
            gui_->init_();
        }
        catch (const nana::place::error& e) {
            std::cerr << "Caught nana::place::error: " << e.what() << std::endl;
            // Avoid rebinding here, just recreate the gui
            gui_.reset(); // Clear the previous instance to avoid issues
            gui_ = std::make_unique<craftory_gui>(wd);
            gui_->init_();
        }
        this->update_labels_thr();
        game_->update_gold_bgps();
        game_->yield_factory_resources<e_resource_type::WOOD, e_resource_type::STONE>();
        bind_click_event(*gui_->gold_click_button_, [this]() { game_->gold_click(); });
        bind_click_event(*gui_->gps_upgrade_button_, [this]() { game_->gps_click(); });
        bind_click_event(*gui_->click_value_upgrade_button_, [this]() { game_->cv_click(); });
        gui_->show();
    }
private:
    void update_labels() {
        gui_->gold_label_->caption(std::to_string(game_->gold_counter) + " golds\n" + std::to_string(game_->gold_per_second) + " per second");
        gui_->gps_upgrade_cost_label_->caption("Upgrade gold per second: " + std::to_string(game_->gps_upgrade_cost));
        gui_->click_value_upgrade_cost_label_->caption("Upgrade click value: " + std::to_string(game_->click_value_upgrade_cost));
    }

    void update_resources_labels() {
        return;
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
    std::unique_ptr<craftory_gui> gui_;
};