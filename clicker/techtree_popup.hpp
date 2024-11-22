#ifndef TECHTREE_POPUP_H
#define TECHTREE_POPUP_H

#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/panel.hpp>
#include <vector>

class techtree_popup : public nana::form
{
public:
    techtree_popup(nana::window& parent)
        : nana::form(parent, nana::rectangle{ 200, 150, 800, 600 })
    {
        caption("Technology Tree");
        init_();
    }

private:
    void init_()
    {
        // Initialize the place for layout
        place_.bind(*this);

        // Create a scrollable panel for the tech tree
        panel_ = std::make_unique<nana::panel<true>>(*this);

        // Define the layout
        place_.div("margin=[10,10,10,10] <vert <weight=50 header><tech_panel>>");

        // Header with title and close button
        header_panel_ = std::make_unique<nana::panel<false>>(*this);
        close_button_ = std::make_unique<nana::button>(*header_panel_);
        title_label_ = std::make_unique<nana::label>(*header_panel_);

        // Setup header
        nana::place header_place{ *header_panel_ };
        header_place.div("margin=5 <weight=200 title><weight=80 close>");

        title_label_->caption("Research Technologies");
        title_label_->text_align(nana::align::left, nana::align_v::center);

        close_button_->caption("Close");
        close_button_->events().click([this] {
            this->close();
            });

        header_place["title"] << *title_label_;
        header_place["close"] << *close_button_;

        // Add example technology buttons
        create_tech_tree();

        // Place the panels
        place_["header"] << *header_panel_;
        place_["tech_panel"] << *panel_;

        // Arrange everything
        place_.collocate();
        header_place.collocate();
    }

    void create_tech_tree()
    {
        // Create a place for the tech tree panel
        tech_place_.bind(*panel_);
        tech_place_.div("margin=[10,10,10,10] <vert gap=10 "
            "<weight=100 tier1>"
            "<weight=100 tier2>"
            "<weight=100 tier3>"
            ">");

        // Create example tech buttons for different tiers
        add_tech_button("Basic Tools", "tier1", "Unlocks basic resource gathering");
        add_tech_button("Advanced Mining", "tier2", "Improves mining efficiency");
        add_tech_button("Automation", "tier3", "Enables automatic resource collection");

        tech_place_.collocate();
    }

    void add_tech_button(const std::string& name, const std::string& tier, const std::string& tooltip)
    {
        auto btn = std::make_unique<nana::button>(*panel_);
        btn->caption(name);
        btn->tooltip(tooltip);
        btn->events().click([name] {
            // Handle technology unlock logic here
            nana::msgbox msg{ "Research"};
            msg.icon(nana::msgbox::icon_information);
            msg.show();
            });

        tech_buttons_.push_back(std::move(btn));
        tech_place_.field(tier.c_str()) << *tech_buttons_.back();
    }

    nana::place place_;
    nana::place tech_place_;
    std::unique_ptr<nana::panel<true>> panel_;
    std::unique_ptr<nana::panel<false>> header_panel_;
    std::unique_ptr<nana::button> close_button_;
    std::unique_ptr<nana::label> title_label_;
    std::vector<std::unique_ptr<nana::button>> tech_buttons_;
};

#endif // TECHTREE_POPUP_H