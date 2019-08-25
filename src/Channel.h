#pragma once

#include<sys/epoll.h>
#include<functional>


//class Epoll;
class EventLoop;


//处理一个fd上的IO事件分发
class Channel
{
private:
    void update();

    typedef std::function<void()> eventHandleFunction;

    EventLoop* loop_;
    const int fd;
    int events, revents;
    eventHandleFunction readCallBack_, writeCallBack_, errorCallBack_;
public:
    Channel() = default;
    Channel(int fdSet,EventLoop* lp);


    void setReadCallBack(const eventHandleFunction& cb)
    {
        readCallBack_ = cb;
    }
    void setWriteCallBack(const eventHandleFunction& cb)
    {
        writeCallBack_ = cb;
    }
    void setErrorCallBack(const eventHandleFunction& cb)
    {
        errorCallBack_ = cb;
    }

    void enableRead()
    {
        events = EPOLLIN | EPOLLHUP | EPOLLET;
        update();
    }

    void enableWrite()
    {
        events |= EPOLLOUT;
        update();
    }

    void disable()
    {
        events = 0;
        update();
    }

    void handleEvent();

    int getCfd() const {return fd;}
    int getCevents() const {return events;}
    void setRevents(int rev)
    {
        revents = rev;

    }
};
