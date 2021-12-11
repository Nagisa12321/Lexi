#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>
#include "GuiFactory.h"
#include "Logger.h"
#include "Window.h"
#include "Commands.h"


class EventListener {
public:
    static void init_listener(const GuiFactory::OS &os, Window *win, int fps);
    static EventListener *get_listener();
    static void destory_listener();
    EventListener(const EventListener &) = delete;
    EventListener& operator=(const EventListener &) = delete;
    virtual ~EventListener();
    virtual void loop() = 0;
    virtual void stop() = 0;
    void add_window(Window *window);
    virtual void close_window(Window *window) = 0;
protected:    
    EventListener(Window *window);
    Window *m_main_window;
    Window *m_current_window;
    std::vector<Window *> m_child_windows;

private:
    static EventListener *manager;
};

class RenderExecutor {
public:
    static void init_executor();
    static RenderExecutor *get_executor();
    static void destory_executor();

    RenderExecutor(const RenderExecutor &) = delete;
    RenderExecutor& operator=(const RenderExecutor &) = delete;
    ~RenderExecutor() {
        Logger::get_logger()->debug("RenderExecutor end safely!\n");
    }

    void put_command(Command *command) {
        BlockingQueueManager::get_manager()->get_randering_queue()->put(command);
    }

    void start() {
        m_running = true;
        for (; m_running; ) {
            Command *c = BlockingQueueManager::get_manager()->get_randering_queue()->take();
            c->exec();
            delete c;
        }
    }

    void stop() {
        BlockingQueueManager::get_manager()->get_randering_queue()->put(new QuitCommand(&m_running));
        while (m_running)
            ;
        Logger::get_logger()->debug("RenderExecutor stop safely!\n");
    }

private:
    static RenderExecutor *exec;
    RenderExecutor()
        : m_running(false)
    {

    }

    bool m_running;
};



class EventExecutor {
public:
    static void init_executor(int threads);
    static EventExecutor *get_executor();
    static void destory_executor();

    EventExecutor(const EventExecutor &) = delete;
    EventExecutor& operator=(const EventExecutor &) = delete;
    ~EventExecutor() {
        for (std::thread *t : m_tvec)
            delete t;
        delete m_running;
        Logger::get_logger()->debug("EventExecutor end safely!\n");
    }

    void put_command(Command *command) {
        BlockingQueueManager::get_manager()->get_task_queue()->put(command);
    }

    void start() {
        *m_running = true;
        auto __run = [=] {
            for (; *m_running; ) {
                Logger::get_logger()->debug("EventExecutor really for get the task. \n");
                Command *c = BlockingQueueManager::get_manager()->get_task_queue()->take();
                Logger::get_logger()->debug("EventExecutor get a tesk. %p\n", c);

                c->exec();
                delete c;
            }
        };
        for (int i = 0; i < m_threads; ++i) {
            m_tvec[i] = new std::thread(__run);
        }
    }

    void stop() {
        Logger::get_logger()->debug("will stop the executor.\n");
        for (int i = 0; i < m_threads; ++i)
            BlockingQueueManager::get_manager()->get_task_queue()->put(new QuitCommand(m_running));
        while (*m_running)
            ;

        for (int i = 0; i < m_threads; ++i)
            m_tvec[i]->join();
    }
private:
    static EventExecutor *exec;
    EventExecutor(int threads)
        : m_tvec(threads),
          m_threads(threads),
          m_running(new bool(false))
    {

    }

    int m_threads;
    std::vector<std::thread *> m_tvec;
    bool *m_running;
};

#endif // EVENTMANAGER_H
