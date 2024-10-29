#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>

#include <thread>
#include <chrono>
#include <memory>
#include <utility>

#include "game.hpp"

uint64_t game::gold_counter = 0;

int main()
{
	std::unique_ptr<game> g = std::make_unique<game>();
	nana::form fm;
	fm.caption("clicker");
	nana::label lbl(fm, nana::rectangle(20, 60, 150, 30));
	nana::button btn(fm, nana::rectangle(20, 20, 150, 30));
	btn.caption("Click me!");
	btn.events().click([&]
		{
			lbl.caption(g->click());
		});
	//g->update_resources();
	fm.show();
	nana::exec(
#ifdef NANA_AUTOMATIC_GUI_TESTING
		2, 1, [&btn]() { click(btn); }
#endif
	);
}