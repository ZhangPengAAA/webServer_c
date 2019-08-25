#pragma once

#include<sys/epoll.h>

#include<map>
#include<vector>
#include<functional>

//#include"Channel.h"

class Channel;
class EventLoop;

class Epoll
{
private:
    //typedef std::function<void()> callBack;
    typedef std::map<int, Channel*> fdToChannel;

    EventLoop* loop_;
    int epollfd;
    fdToChannel fd_Channel;
    int nactiveFds = 0;
    struct epoll_event actEpollEvents[100];
public:
    //Epoll(){}
    Epoll(EventLoop* lp);

    void runEpoll();
    void updateChannel(Channel* cl);
    void removeChannel(Channel* cl);

    Channel* getChannel(int fd)
    {
        return fd_Channel[fd];
    }

    int getActFds()
    {
        return nactiveFds;
    }
    struct epoll_event* getActEvents()
    {
        return actEpollEvents;
    }
};
