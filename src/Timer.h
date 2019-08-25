#pragma once
//#include<sys/time.h>
#include<sys/timerfd.h>
#include<map>
#include<functional>


typedef std::function<void()> timeCallBack;

class EventLoop;
class Channel;
class TimerEle
{
private:
    timeCallBack tcb;
    int64_t when;
    double interval;//暂时用秒来存储，以后修改
    bool repeat;
public:
    TimerEle(const timeCallBack& cb, int64_t wh, double interl = 0) : tcb(cb),
                                                                           when(wh),
                                                                           interval(interl),
                                                                           repeat(interl>0)
    { }
    int64_t getTimerWhen(){ return when; }
    bool isRepeat() { return repeat == 1; }
    double getInterval() { return interval; }
    void run(){ tcb(); }
};

class TimerManager
{
private:
    typedef std::multimap<int64_t, TimerEle*> timerMapType;
    timerMapType timerMap;

    int timerFd;
    Channel* timerChannel;
    EventLoop* loop;
public:
    TimerManager(EventLoop* lp);

    //下面两个函数都借用timerfd_settime的相对时间来实现，后边可以实现绝对时间的版本
    void handleTimers();
    void addTimer(int64_t times, const timeCallBack& cb, double inter);
};
