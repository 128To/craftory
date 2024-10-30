#pragma once

#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>

#include <thread>
#include <chrono>
#include <memory>

#include "game.hpp"

class GameUI {
public:
    GameUI(std::unique_ptr<game> game) : game_(std::move(game)), fm_() {
        fm_.caption("Clicker");

        // Use layout management (example with nana::place)
        nana::place layout(fm_);
        layout.div("<vert margin=10 gap=10 <weight=30><weight=20% labels> <weight=40% buttons>");

        goldLabel_ = std::make_unique<nana::label>(fm_);
        layout["labels"] << *goldLabel_;
        gpsLabel_ = std::make_unique<nana::label>(fm_);
        layout["labels"] << *gpsLabel_;

        clickButton_ = std::make_unique<nana::button>(fm_);
        clickButton_->caption("Click me!");
        layout["buttons"] << *clickButton_;

        // --- Upgrades Section ---
        gpsUpgradeButton_ = std::make_unique<nana::button>(fm_);
        gpsUpgradeButton_->caption("Upgrade GPS");
        layout["upgrades"] << *gpsUpgradeButton_;

        gpsUpgradeCostLabel_ = std::make_unique<nana::label>(fm_);
        layout["upgrades"] << *gpsUpgradeCostLabel_;
        // ... (Add resource labels dynamically here)

        layout.collocate();

        updateLabels();

        clickButton_->events().click([this]() {
            game_->click();
            updateLabels();
            });

        fm_.show();
    }
private:
    void updateLabels() {
        goldLabel_->caption(std::to_string(game_->gold_counter) + " golds");
        gpsLabel_->caption(game_->gold_per_second + " per second");
        gpsUpgradeCostLabel_->caption("Upgrade Cost: " + std::to_string(game_->gps_upgrade_cost));
        // ... (Update resource labels) 
    }

    std::unique_ptr<game> game_;
    nana::form fm_;
    std::unique_ptr<nana::label> goldLabel_;
    std::unique_ptr<nana::label> gpsLabel_;
    std::unique_ptr<nana::button> clickButton_;
    std::unique_ptr<nana::button> gpsUpgradeButton_;
    std::unique_ptr<nana::label> gpsUpgradeCostLabel_;
    // ... (Store resource labels)
};