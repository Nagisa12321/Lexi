#ifndef COMMANDS_H
#define COMMANDS_H
#include <string>
#include <mutex>
#include <condition_variable>
#include <list>
 
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

class CommandQueue {
public:
    CommandQueue(int count);
    CommandQueue(const CommandQueue &) = delete;
    ~CommandQueue();
    CommandQueue &operator=(const CommandQueue &) = delete;

    Command *take();
    void put(Command *cmd);
    void clear();
private:
    Semephore m_free;
    Semephore m_product;
    std::mutex m_list_lock;
    std::list<Command *> m_command_list;
    bool m_cleared;
};

class CommandQueueManager {
public:
    static void init_manager();
    static CommandQueueManager *get_manager();
    static CommandQueueManager *destory_manager();
    ~CommandQueueManager();
    CommandQueueManager(const CommandQueueManager &) = delete;
    CommandQueueManager &operator=(const CommandQueueManager &) = delete;

    CommandQueue *get_randering_queue();
private:
    CommandQueueManager();
    static CommandQueueManager *manager;
    CommandQueue *m_rendering_queue;
};

#endif // COMMANDS_H
