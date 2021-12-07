#include "LinuxEvents.h"
#include "Commands.h"
#include "EventManager.h"
#include "Events.h"
#include "LinuxWindowImpl.h"
#include "LinuxCommands.h"
#include "SDL.h"
#include "SDL_timer.h"
#include "Window.h"
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <thread>
using namespace std;

LinuxEventListener::LinuxEventListener(Window *window, int fps) :
    EventListener(window),
    m_fps(fps),
    m_running(true),
    m_stopped(false),
    m_event_thread()
{

}

void __delete_window(Window *win) {
    if (!win) return;
    BlockingQueueManager *manager = BlockingQueueManager::get_manager();
    manager->get_delete_window_queue()->put(win);
    manager->get_randering_queue()->put(new DeleteWindow());
}

void LinuxEventListener::loop() {
    /* fix code here */
    auto run = [=] {
        int delay = 1000 / m_fps;
        while (m_running) {
            SDL_Delay(delay);
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_QUIT:
                    printf("exit!\n");  
                    m_running = false;
                    break;
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                        printf("window close!\n");
                        // ... Handle window close for each window ...
                        // Note, you can also check e.window.windowID to check which
                        // of your windows the event came from.
                        // e.g.:
                        // if it is the main window:
                        if (SDL_GetWindowID(((LinuxWindowImpl *)(m_main_window->get_impl()))->get_window())
                            == event.window.windowID) {
                            m_running = false;
                            break;
                        } else {
                            auto cur = m_child_windows.begin();
                            /* TODO: fix bug here */
                            while (cur != m_child_windows.end()) {
                                if (SDL_GetWindowID(((LinuxWindowImpl *)((*cur)->get_impl()))->get_window())
                                    == event.window.windowID) {
                                    __delete_window(*cur);
                                    m_child_windows.erase(cur);
                                    m_current_window = m_main_window;
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
                    EventExecutor::get_executor()->put_command(new ProcessEvent(m_current_window, 
                        new MousePressEvent({event.button.x, event.button.y}, false)));
                    m_current_window->draw(m_current_window);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    EventExecutor::get_executor()->put_command(new ProcessEvent(m_current_window, 
                        new MousePressEvent({event.button.x, event.button.y}, true)));                    
                    m_current_window->draw(m_current_window);
                    break;
                case SDL_MOUSEWHEEL:
                    // fprintf(stdout, "[%d ms] MouseWheel\ttype:%d\tid:%d\tx:%d\ty:%d\n",
                    // 	event.wheel.timestamp, event.wheel.type, event.wheel.which, event.wheel.x, event.wheel.y);
                    break;
                case SDL_KEYUP:
                    break;
                case SDL_KEYDOWN:
                    // fprintf(stdout, "[%d ms] Keyboard\ttype:%d\twindowID:%d\tsym:%c\tmodifiers:%d\tstate:%d\trepeat:%d\n",
                    //         event.key.timestamp, event.key.type, event.key.windowID, event.key.keysym.sym, event.key.keysym.mod, event.key.state, event.key.repeat);
                    break;
                default:
                    break;
                }
            }
        }

        // put the quit event
        RenderExecutor::destory_executor();

        cout << "put the quit." << endl;
        m_stopped = true;
    };

	std::thread t(run);
    m_event_thread.swap(t);
}


void LinuxEventListener::stop() {
    m_running = false;
    m_event_thread.join();

    while (!m_stopped)
        ;

    cout << "well stopped!" << endl;
}
