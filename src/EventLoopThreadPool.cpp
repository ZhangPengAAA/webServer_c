#include<vector>
#include"EventLoopThread.h"
#include"EventLoopThreadPool.h"
#include<iostream>



EventLoopThreadPool::EventLoopThreadPool(EventLoop* lp) : baseLoop(lp),
                                                          index(0)
{ }

void EventLoopThreadPool::createThread(int num)
{
    for(int i = 0; i < num; ++i)
    {
        EventLoopThread* lp = new EventLoopThread();
        threads.push_back(lp);
    }
}

EventLoop* EventLoopThreadPool::getNextLoop()
{
    if(threads.empty())
        return nullptr;
    std::cout << "getNextLoop\n";
    EventLoop* lp = threads[(index%threads.size())]->getLoop();
    std::cout << "error?\n";
    ++index;

    return lp;
}
