#include<vector>

class EventLoopThread;
class EventLoop;

class EventLoopThreadPool
{
private:
    std::vector<EventLoopThread*> threads;
    EventLoop* baseLoop;
    int index;
public:
    EventLoopThreadPool(EventLoop* lp);
    void createThread(int num);
    EventLoop* getNextLoop();
    int getPoolSize() { return threads.size(); }
};
