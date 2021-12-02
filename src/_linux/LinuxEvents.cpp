#include "LinuxEvents.h"
#include "EventManager.h"
#include "Events.h"
#include "LinuxWindowImpl.h"
#include "SDL.h"
#include "SDL_timer.h"
#include "Window.h"
#include <cstdio>
#include <vector>
using namespace std;

LinuxEventManager::LinuxEventManager(Window *window, int fps) 
    : EventManager(window),
      m_fps(fps)
{

}


void LinuxEventManager::loop() {
    int delay = 1000 / m_fps;
    bool running = true;
    while (running) {
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				printf("exit!\n");
				// delete the window
				delete m_main_window;
				m_main_window = nullptr;
				running = false;
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
					printf("wndow close!\n");
					// ... Handle window close for each window ...
					// Note, you can also check e.window.windowID to check which
					// of your windows the event came from.
					// e.g.:
					// if it is the main window: 
					if (SDL_GetWindowID(((LinuxWindowImpl *)(m_main_window->get_impl()))->get_window()) 
							== event.window.windowID) {
						delete m_main_window;
						m_main_window = nullptr;
						running = false;
						break;
					} else {
						auto cur = m_child_windows.begin();
						while (cur != m_child_windows.end()) {
							if (SDL_GetWindowID(((LinuxWindowImpl *)((*cur)->get_impl()))->get_window())
								== event.window.windowID) {
								delete *cur;
								m_child_windows.erase(cur);
								break;
							}
						}
					}
				}
				break;
			case SDL_MOUSEMOTION:
				// fprintf(stdout, "[%d ms] MouseMotion\ttype:%d\twhich:\tx:%d\ty:%d\txrel:%d\tyrel:%d\n",
				// 	event.motion.timestamp, event.motion.type, event.motion.which, event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
				break;
			case SDL_MOUSEBUTTONUP:
				m_current_window->process_event(MousePressEvent({event.button.x, event.button.y}, false));
				m_current_window->draw(m_current_window);
				break;
			case SDL_MOUSEBUTTONDOWN:
				m_current_window->process_event(MousePressEvent({event.button.x, event.button.y}, true));
				m_current_window->draw(m_current_window);
				break;
			case SDL_MOUSEWHEEL:
				// fprintf(stdout, "[%d ms] MouseWheel\ttype:%d\tid:%d\tx:%d\ty:%d\n",
				// 	event.wheel.timestamp, event.wheel.type, event.wheel.which, event.wheel.x, event.wheel.y);
				break;
			case SDL_KEYUP:
				break;
			case SDL_KEYDOWN:
				fprintf(stdout, "[%d ms] Keyboard\ttype:%d\twindowID:%d\tsym:%c\tmodifiers:%d\tstate:%d\trepeat:%d\n",
					event.key.timestamp, event.key.type, event.key.windowID, event.key.keysym.sym, event.key.keysym.mod, event.key.state, event.key.repeat);
				break;
			default:
				fprintf(stdout, "Some event\n");
				break;
			}
		}
        SDL_Delay(delay);
	}
}
