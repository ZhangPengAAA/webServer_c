#include"Timer.h"
#include"Channel.h"
#include"EventLoop.h"
#include<iostream>

#include<sys/time.h>
#include<functional>
#include<vector>
#include<pthread.h>

TimerManager::TimerManager(EventLoop* lp) : loop(lp),
                                            timerFd(timerfd_create(CLOCK_MONOTONIC, TFD_CLOEXEC | TFD_NONBLOCK)),
                                            timerChannel(new Channel(timerFd, lp))
{
    timerChannel->setReadCallBack(std::bind(&TimerManager::handleTimers,this));
    timerChannel->enableRead();
    //std::cout << "chu shi: isEmpty? " << timerMap.empty() << std::endl;
}

void TimerManager::handleTimers()
{
    std::vector<TimerEle*> expired;
    struct timeval now;
    gettimeofday(&now, nullptr);

    int64_t intNow = now.tv_sec*1000000 + now.tv_usec;
    //获取到时的timer，分别处理timer事件
    auto it = timerMap.upper_bound(intNow);
    for(auto itb = timerMap.begin(); itb != it; ++it)
        expired.push_back(itb->second);
    if(timerMap.size() == 1)
        timerMap.clear();
    else
        timerMap.erase(timerMap.begin(), it);
    for(auto& x : expired)
    {
        x->run();
        if(x->isRepeat()){
             timerMap.insert(std::pair<int64_t,TimerEle*>(x->getInterval()*1000000 + intNow, x));
        }
        else
            delete x;
    }
    //重新设定定时器timerfd_settime
    struct itimerspec newTime;
    if(timerMap.empty()){
        newTime.it_value = {0,0};
        timerfd_settime(timerFd, 1, &newTime, nullptr);
    }else{
        it = timerMap.begin();
        //std::cout << it->first << "\n" << intNow << std::endl;
        newTime.it_value.tv_sec = (it->first-intNow)/1000000;
        newTime.it_value.tv_nsec = 0;
        newTime.it_interval = {1,0};
        //std::cout << newTime.it_value.tv_sec << std::endl;
        //std::cout << "here\n";
        timerfd_settime(timerFd, 0, &newTime, nullptr);
    }
}
//未完成
void TimerManager::addTimer(int64_t times, const timeCallBack& cb, double inter)
{
    if(pthread_self() != loop->threadID){
        //std::cout << "diao yong threadid: " << pthread_self() << "\n";
         throw 1;
    }
    TimerEle* timerPtr = new TimerEle(cb, times, inter);
    timerMap.insert(std::pair<int64_t,TimerEle*>(times, timerPtr));
    if(timerMap.empty() || times <= timerMap.begin()->first){
       // std::cout << "empty\n";
        struct itimerspec newTime;
        struct timeval now;
        gettimeofday(&now, nullptr);
        int64_t intNow = now.tv_sec*1000000 + now.tv_usec;

        newTime.it_value.tv_sec = (times-intNow)/1000000;
        newTime.it_value.tv_nsec = ((times-intNow)%1000000)*1000;
        newTime.it_interval= {1,0};
        int64_t ti = newTime.it_value.tv_sec*1000000 + newTime.it_value.tv_nsec/1000;
        timerfd_settime(timerFd, 0, &newTime, nullptr);
        //std::cout << "seted\n";
    }else{
        return;
    }
/*
    TimerEle* timerPtr = new TimerEle(cb, times, 0);
    timerMap.insert(std::pair<int64_t,TimerEle*>(times, timerPtr));
    if(timerMap.empty() || times <= timerMap.begin()->first){
        struct itimerspec newTime;
        newTime.it_value.tv_sec = times/1000000;
        newTime.it_value.tv_nsec = (times%1000000)*1000;
        newTime.it_interval= {0,0};
        int64_t ti = newTime.it_value.tv_sec*1000000 + newTime.it_value.tv_nsec/1000;


        struct timeval now;
        gettimeofday(&now, nullptr);

        std::cout << "\n\n\n" << now.tv_sec*1000000 + now.tv_usec << "\n";
        std::cout << times << std::endl;
        std::cout <<  ti << std::endl;
        timerfd_settime(timerFd, 1, &newTime, nullptr);
        std::cout << "seted\n";
    }else{
        return;
    }
*/
}


