#include "Commands.h"
#include "Logger.h"
#include <cstdio>
#include <mutex>
#include <string>
#include <iostream>

using namespace std;

const int default_init_count = 100;
bool Command::__debug = true;
BlockingQueueManager *BlockingQueueManager::manager = 0;


Command::Command(std::string command_name)
    : m_command_name(command_name),
      __m_debug(new int)
{

}

void Command::exec() {
    if (__debug)
        cout << "run [" << m_command_name << "]" << endl; 
}

Command::~Command() { delete __m_debug; }


Semephore::Semephore(int count)
    : count(count),
        m(),
        cv()
{

}

void Semephore::await() {
    std::unique_lock<std::mutex> lk(m);
    if (--count < 0) { cv.wait(lk); }
}

void Semephore::post() {
    std::unique_lock<std::mutex> lk(m);
    if (++count <= 0) { cv.notify_one(); }
}

Semephore::~Semephore() { cv.notify_all(); }

void BlockingQueueManager::init_manager() {
    // static CommandQueueManager m;
    // manager = &m;
    manager = new BlockingQueueManager();
}

BlockingQueueManager *BlockingQueueManager::get_manager() {
    return manager;
}

void BlockingQueueManager::destory_manager() {
    delete manager;
}


BlockingQueueManager::BlockingQueueManager()
    : m_rendering_queue(new BlockQueue<Command *>(default_init_count)),
      m_tasks_queue(new BlockQueue<Command *>(default_init_count)),
      m_new_window_queue(new BlockQueue<Window *>(default_init_count)),
      m_delete_window_queue(new BlockQueue<Window *>(default_init_count))
{

}

BlockingQueueManager::~BlockingQueueManager() { 
    delete m_rendering_queue; 
    delete m_new_window_queue; 
    delete m_delete_window_queue; 
    delete m_tasks_queue; 
}

BlockQueue<Command *> *BlockingQueueManager::get_randering_queue() { return m_rendering_queue; }
BlockQueue<Command *> *BlockingQueueManager::get_task_queue() { return m_tasks_queue; }
BlockQueue<Window *> *BlockingQueueManager::get_new_window_queue() { return m_new_window_queue; }
BlockQueue<Window *> *BlockingQueueManager::get_delete_window_queue() { return m_new_window_queue; }
