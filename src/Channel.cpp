#include"Channel.h"
#include"EventLoop.h"
#include<iostream>

//#include<iostream>


Channel::Channel(int fdSet, EventLoop* lp) :
                                        fd(fdSet),
                                        events(0),
                                        revents(0),
                                        loop_(lp)
{ }



void Channel::handleEvent()
{
    if(revents & EPOLLHUP)
        std::cout << "hup signal\n";
    if(revents & EPOLLIN)
    {
        if(readCallBack_)
            readCallBack_();
    }
       // readCallBack_();
    if(revents & EPOLLOUT)
        writeCallBack_();
    if(revents & EPOLLERR)
        errorCallBack_();
}


void Channel::update()
{
    loop_->updateChannel(this);
}


/*
void rcb()
{
    std::cout << "read" << std::endl;
}

void wcb()
{
    std::cout << "write" << std::endl;
}

void ecb()
{
    std::cout << "error" << std::endl;
}
int main()
{
    Channel channel(0);
    channel.setReadCallBack(rcb);
    channel.setWriteCallBack(wcb);
    channel.setErrorCallBack(ecb);

    channel.handleRead();
    channel.handleWrite();
    channel.handleError();

    return 0;
}
*/
