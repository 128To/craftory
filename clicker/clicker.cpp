#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>

#include <thread>
#include <chrono>

int main()
{
	nana::form fm;
	fm.caption("clicker");
	nana::label lbl(fm, nana::rectangle(20, 60, 150, 30));
	nana::button btn(fm, nana::rectangle(20, 20, 150, 30));
	btn.caption("Click me!");
	static int mat = 0;
	btn.events().click([&]
		{
			lbl.caption(std::to_string(mat++));
		});

	// Idle generation every second
	std::thread idleThread([&]() {
		while (true) {
			std::this_thread::sleep_for(std::chrono::seconds(1));
			lbl.caption(std::to_string(mat++));
		}
		});
	idleThread.detach(); // Let the thread run in the background

	fm.show();
	nana::exec(
#ifdef NANA_AUTOMATIC_GUI_TESTING
		2, 1, [&btn]() { click(btn); }
#endif
	);
}