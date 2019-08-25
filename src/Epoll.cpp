#include"Epoll.h"


#include<assert.h>
//#include<sys/epoll.h>
#include<iostream>

#include"Channel.h"

Epoll::Epoll(EventLoop* lp): loop_(lp)
{
    epollfd = epoll_create(10000);
}

void Epoll::runEpoll()
{
    std::cout << "fd_Channel.size: " << fd_Channel.size() << "\n";//初始是二个timefd\eventfd
    //std::cout << "fd_Channel.1: " << fd_Channel.begin()->first << "\n";
    //std::cout << "fd_Channel.1: " << (++fd_Channel.begin())->first << "\n";
    nactiveFds = epoll_wait(epollfd, actEpollEvents, 100, -1);
    //std::cout << "pollback\n";
}

void Epoll::updateChannel(Channel* cl)
{
    int fd = cl->getCfd();
    if(fd_Channel.find(fd) == fd_Channel.end())
    {
        fd_Channel[fd] = cl;
        struct epoll_event ev;
        ev.events = cl->getCevents();
        ev.data.fd = fd;
        epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
    }else{
        //Channel& fd_cl = fd_Channel[fd];
        struct epoll_event ev;
        ev.events = cl->getCevents();
        epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
    }
}

void Epoll::removeChannel(Channel* cl)
{
    int fd = cl->getCfd();
    delete fd_Channel[fd];
    fd_Channel.erase(fd);
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL);
}






