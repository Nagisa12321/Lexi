#include "Commands.h"
#include <mutex>
#include <string>
#include <iostream>

using namespace std;

const int default_init_count = 100;
bool Command::__debug = true;
CommandQueueManager *CommandQueueManager::manager = 0;


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
    if (++count <= 0) { cv.notify_all(); }
}

Semephore::~Semephore() { cv.notify_all(); }

CommandQueue::CommandQueue(int count) 
    : m_free(count),
      m_product(0),
      m_command_list(),
      m_list_lock(),
      m_cleared(false)
{

}

CommandQueue::~CommandQueue() {
    for (Command *cmd : m_command_list)
        delete cmd;
}

Command *CommandQueue::take() {
    Command *res;
    m_product.await();
    // 'this' maybe have broken!
    {
        std::unique_lock<std::mutex> lk(m_list_lock);
        if (m_cleared) return nullptr;
        else {
            res = m_command_list.front();
            m_command_list.pop_front();
        }
    }
    m_free.post();
    return res;
}

void CommandQueue::put(Command *cmd) {
    m_free.await();
    {
        std::unique_lock<std::mutex> lk(m_list_lock);
        if (m_cleared) {
            delete cmd;
            return;
        } else {
            m_command_list.push_back(cmd);
        }
    }
    m_product.post();
}

void CommandQueue::clear() {
    {
        std::unique_lock<std::mutex> lk(m_list_lock);
        m_cleared = true;
        for (Command *cmd : m_command_list)
            delete cmd;
        m_command_list.clear();
    }

    // wake up
    m_free.post();
    m_product.post();
    cout << "clear() ok" << endl;
}

void CommandQueueManager::init_manager() {
    // static CommandQueueManager m;
    // manager = &m;
    manager = new CommandQueueManager();
}

CommandQueueManager *CommandQueueManager::get_manager() {
    return manager;
}

CommandQueueManager *CommandQueueManager::destory_manager() {
    delete manager;
}


CommandQueueManager::CommandQueueManager()
    : m_rendering_queue(new CommandQueue(default_init_count))
{

}

CommandQueueManager::~CommandQueueManager() { delete m_rendering_queue; }

CommandQueue *CommandQueueManager::get_randering_queue() { return m_rendering_queue; }
