#include"EventLoop.h"
#include"Epoll.h"
#include"Channel.h"
#include"Timer.h"
#include<sys/eventfd.h>
#include<unistd.h>
#include<iostream>
#include<functional>


EventLoop::EventLoop() : loopPoll(new Epoll(this)),
                         tm(new TimerManager(this)),
                         eventFd(eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK)),
                         eventFdChannel(new Channel(eventFd, this)),
                         isRunningPendingFunctors(0),
                         threadID(pthread_self())
{
    pthread_mutex_init(&functorMutex, NULL);
    eventFdChannel->enableRead();
    //std::cout << "eventFd: " << eventFd;
}

void EventLoop::loop()
{
    for(;;)
    {
        loopPoll->runEpoll();
        for(int i = 0; i < loopPoll->getActFds(); ++i)
        {
            struct epoll_event& temp = loopPoll->getActEvents()[i];
            int fd = temp.data.fd;
            Channel* cc = loopPoll->getChannel(fd);
            cc->setRevents(temp.events);
            cc->handleEvent();
            cc->setRevents(0);
        }
        doPendingFunctors();
    }
}

void EventLoop::updateChannel(Channel* cl)
{
    loopPoll->updateChannel(cl);
}

void EventLoop::runAt(int64_t times, const timeCallBack& cb, double inter)
{
    runInLoop(bind(&TimerManager::addTimer, tm, times, cb, inter));//这里将addtimer函数放到runinloop中调用，可以实现，让非loop线程调用loop的runat函数
                                            //addtimer函数是线程安全的，当非loop线程运行它时，会报错。因而加上runinloop就可以正常调用，且在loop线程执行。
    //tm->addTimer(times, cb, inter);
}

void EventLoop::doPendingFunctors()
{
    //std::cout << "dopendingfunctors\n";
    pthread_mutex_lock(&functorMutex);
    std::vector<timeCallBack> emptyFunctors;
    emptyFunctors.swap(functors);
    pthread_mutex_unlock(&functorMutex);
    isRunningPendingFunctors = true;

    for(auto& x : emptyFunctors)
    {
        x();
    }
    isRunningPendingFunctors  = false;
}

void EventLoop::wakeup()
{
    //std::cout << "wakeup" << functors.size() << "\n";
    uint64_t al = 1;//这里必须用uint64_t类型，而不能用int，否则写入失败。
    int n = write(eventFd, &al, sizeof(al));
    //std::cout << "write number: " << n << "\n";
}

void EventLoop::runInLoop(const timeCallBack& cb)
{
    //std::cout << "runinLoop\n";
    if(pthread_self() == threadID)
        cb();
    else
        queueInLoop(cb);
}

void EventLoop::queueInLoop(const timeCallBack& cb)
{
    //std::cout << "queueinLoop\n";
    pthread_mutex_lock(&functorMutex);
    functors.push_back(cb);
    pthread_mutex_unlock(&functorMutex);
    if(pthread_self() != threadID || isRunningPendingFunctors)
    {
        wakeup();
    }
}

void EventLoop::removeChannel(Channel* cl)
{
    loopPoll->removeChannel(cl);
}
