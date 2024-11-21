#ifndef CRAFTORY_GUI_H
#define CRAFTORY_GUI_H

#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>

class craftory_gui : public nana::form
{
public:
    craftory_gui(nana::window& parent, const ::nana::size& sz = { 1280, 720 }, const nana::appearance& apr = { true, true, false, false, false, false, false })
        : nana::form(parent, sz, apr)
    {
        init_();
    }

	~craftory_gui()
	{
		//<*dtor

		//*>
	}

    void init_()
    {
        //nana::API::zoom_window(*this, true);
        if (!place_.window_handle()) {
            place_.bind(*this);
        }

        place_.div("margin=[5,5,5,5] "
                    "<vert margin=[5,5,5,5] "
                        "<grid=[1,5] margin=[5,5,5,5] gap=10 grid1>"
                        "<margin=[5,5,5,5] "
                            "<grid=[1,5] margin=[5,5,5,5] gap=2 grid3>"
                        ">"
                    ">"
                    "<margin=[5,5,5,5] "
                        "<margin=[5,5,5,5] "
                            "<grid=[1,8] margin=[5,5,5,5] gap=2 grid2>"
                        ">"
                        "<grid=[1,8] margin=[5,5,5,5] gap=2 grid21>"
                    ">"
                    "<margin=[5,5,5,5] "
                        "<margin=[5,5,5,5] "
                            "<grid=[1,8] margin=[5,5,5,5] gap=2 grid22>"
                        ">"
                        "<grid=[1,8] margin=[5,5,5,5] gap=2 grid211>"
                    ">"
                    "<margin=[5,5,5,5] gap=2 field6>");
		caption("Craftory");
        bgcolor(nana::color(230, 230, 230));

        // gold_label_
        gold_label_ = std::make_unique<nana::label>(*this);
        place_["grid1"] << *gold_label_;
        gold_label_->bgcolor(nana::color(230, 230, 230));
        gold_label_->typeface(nana::paint::font("", 15, { 400, false, false, false }));
        gold_label_->caption("0 Gold(s).\n 0 per seconds");
        gold_label_->format(true);
        gold_label_->text_align(static_cast<nana::align>(1), static_cast<nana::align_v>(1));

        // gold_click_button_
        gold_click_button_ = std::make_unique<nana::button>(*this);
        place_["grid1"] << *gold_click_button_;
        gold_click_button_->caption("Click me!");

        // resource_label_
        resource_label_ = std::make_unique<nana::label>(*this);
        place_["grid3"] << *resource_label_;
        resource_label_->caption("Wood : 0");
        resource_label_->text_align(static_cast<nana::align>(1), static_cast<nana::align_v>(1));

        // resource_label__
        resource_label__ = std::make_unique<nana::label>(*this);
        place_["grid3"] << *resource_label__;
        resource_label__->caption("Stone : 0");
        resource_label__->text_align(static_cast<nana::align>(1), static_cast<nana::align_v>(1));

        // click_value_upgrade_button_
        click_value_upgrade_button_ = std::make_unique<nana::button>(*this);
        place_["grid2"] << *click_value_upgrade_button_;
        click_value_upgrade_button_->caption("Click value");

        // gps_upgrade_button_
        gps_upgrade_button_ = std::make_unique<nana::button>(*this);
        place_["grid2"] << *gps_upgrade_button_;
        gps_upgrade_button_->caption("Gold per second");

        // click_value_upgrade_cost_label_
        click_value_upgrade_cost_label_ = std::make_unique<nana::label>(*this);
        place_["grid21"] << *click_value_upgrade_cost_label_;
        click_value_upgrade_cost_label_->caption("Cost: 0 gold(s)");
        click_value_upgrade_cost_label_->text_align(static_cast<nana::align>(1), static_cast<nana::align_v>(1));

        // gps_upgrade_cost_label_
        gps_upgrade_cost_label_ = std::make_unique<nana::label>(*this);
        place_["grid21"] << *gps_upgrade_cost_label_;
        gps_upgrade_cost_label_->caption("Cost: 0 gold(s)");
        gps_upgrade_cost_label_->text_align(static_cast<nana::align>(1), static_cast<nana::align_v>(1));

        // build_building_button_
        build_building_button_ = std::make_unique<nana::button>(*this);
        place_["grid22"] << *build_building_button_;
        build_building_button_->caption("Build Sawmill");

        // build_building_button__
        build_building_button__ = std::make_unique<nana::button>(*this);
        place_["grid22"] << *build_building_button__;
        build_building_button__->caption("Build Carrier");

        // building_label_
        building_label_ = std::make_unique<nana::label>(*this);
        place_["grid211"] << *building_label_;
        building_label_->typeface(nana::paint::font("", 8, { 400, false, false, false }));
        building_label_->caption("0 Sawmill(s). Cost: 0 gold(s)");
        building_label_->format(true);
        building_label_->text_align(static_cast<nana::align>(1), static_cast<nana::align_v>(1));

        // building_label__
        building_label__ = std::make_unique<nana::label>(*this);
        place_["grid211"] << *building_label__;
        building_label__->typeface(nana::paint::font("", 8, { 400, false, false, false }));
        building_label__->caption("0 Carrier(s). Cost: 0 gold(s)");
        building_label__->format(true);
        building_label__->text_align(static_cast<nana::align>(1), static_cast<nana::align_v>(1));

        place_.collocate();
    }

    nana::place place_;
    std::unique_ptr<nana::label> gold_label_;
    std::unique_ptr<nana::button> gold_click_button_;
    std::unique_ptr<nana::label> resource_label_;
    std::unique_ptr<nana::label> resource_label__;
    std::unique_ptr<nana::button> click_value_upgrade_button_;
    std::unique_ptr<nana::button> gps_upgrade_button_;
    std::unique_ptr<nana::label> click_value_upgrade_cost_label_;
    std::unique_ptr<nana::label> gps_upgrade_cost_label_;
    std::unique_ptr<nana::button> build_building_button_;
    std::unique_ptr<nana::button> build_building_button__;
    std::unique_ptr<nana::label> building_label_;
    std::unique_ptr<nana::label> building_label__;
};

#endif //CRAFTORY_GUI_H

