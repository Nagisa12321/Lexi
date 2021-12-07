#ifndef COMMANDS_H
#define COMMANDS_H
#include <iostream>
#include <string>
#include <mutex>
#include <condition_variable>
#include <list>
#include "Glyph.h"
#include "Logger.h"
 
extern const int default_init_count;

class Command {
public:
    Command(std::string command_name);
    virtual void exec();
    virtual ~Command();
    static bool __debug;
private:
    std::string m_command_name;
    int     *__m_debug;
};

class Semephore {
public:
    Semephore(int count = 0);
    void await();
    void post();
    ~Semephore();
private:
    int count;
    std::mutex m;
    std::condition_variable cv;
};

template <typename _Tp>
class BlockQueue {
public:
    BlockQueue(int count)
        : m_free(count),
          m_product(0),
          m_list()
    {

    }
    BlockQueue(const BlockQueue &) = delete;
    ~BlockQueue() {
        if (!m_list.empty())
            Logger::get_logger()->debug("warnning! there is still command in the queue.\n");
    }
    BlockQueue &operator=(const BlockQueue &) = delete;

    _Tp take() {
        _Tp res;
        m_product.await();
        res = m_list.front();
        m_list.pop_front();
        m_free.post();
        return res;
    }
    void put(_Tp __val) {
        m_free.await();
        m_list.push_back(__val);
        m_product.post();
    }
private:
    Semephore m_free;
    Semephore m_product;
    std::list<_Tp> m_list;
};

class BlockingQueueManager {
public:
    static void init_manager();
    static BlockingQueueManager *get_manager();
    static void destory_manager();
    ~BlockingQueueManager();
    BlockingQueueManager(const BlockingQueueManager &) = delete;
    BlockingQueueManager &operator=(const BlockingQueueManager &) = delete;

    BlockQueue<Window *> *get_new_window_queue();
    BlockQueue<Window *> *get_delete_window_queue();
    BlockQueue<Command *> *get_randering_queue();
    BlockQueue<Command *> *get_task_queue();
private:
    BlockingQueueManager();
    static BlockingQueueManager *manager;
    BlockQueue<Command *> *m_tasks_queue;
    BlockQueue<Command *> *m_rendering_queue;
    BlockQueue<Window *> *m_new_window_queue;
    BlockQueue<Window *> *m_delete_window_queue;
};

class QuitCommand : public Command {
public:
    QuitCommand(bool *running)
        : Command("kill command."),
          m_running(running)
    {
    }   
    void exec() override {
        Command::exec();
        *m_running = false;
    }
    ~QuitCommand() = default;
private:
    bool *m_running;
};


#endif // COMMANDS_H
