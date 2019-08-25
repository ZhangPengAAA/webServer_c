#pragma once
#include<functional>
#include<pthread.h>
#include<vector>

class TimerManager;
class Epoll;
class Channel;

typedef std::function<void()> timeCallBack;

class EventLoop
{
public:
    Epoll* loopPoll;
    TimerManager* tm;

    int eventFd;
    pthread_t threadID;
    bool isRunningPendingFunctors;
    Channel* eventFdChannel;
    pthread_mutex_t functorMutex;
    std::vector<timeCallBack> functors;
public:
    EventLoop();
    void loop();
    void updateChannel(Channel* cl);
    void runAt(int64_t times, const timeCallBack& cb, double inter);

    void removeChannel(Channel* cl);

    void wakeup();//向eventfd写一个数字，来唤醒epoll，进而唤醒loop线程
    void doPendingFunctors();
    void queueInLoop(const timeCallBack& cb);
    void runInLoop(const timeCallBack& cb);// runinloop函数主要是供本loop线程下属的计算线程来调用，一般是在channel的handleevent函数中会跳到其他线程，然后在这个线程里调用runinloop，能够将一个函数在loop线程运行
};
