//#define NANA_AUTOMATIC_GUI_TESTING // testing purpose
#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>

#include <thread>
#include <chrono>
#include <memory>
#include <utility>

#include "gameui.hpp"


// static definition of initial cost
uint64_t game::gold_counter = 0;
uint64_t game::gps_upgrade_cost = 10;
uint64_t game::click_value_upgrade_cost = 20;


int main() {
    std::unique_ptr<game> g = std::make_unique<game>();
    GameUI gameUI(std::move(g));

    nana::exec(
#ifdef NANA_AUTOMATIC_GUI_TESTING
        2, 1, [&]() { gameUI.clickButton_->events().emit(nana::arg_click, gameUI.fm_); }
#endif
    );
}