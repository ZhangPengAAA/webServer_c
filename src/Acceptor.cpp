#include"Acceptor.h"
#include"Channel.h"
#include"EventLoop.h"

#include<iostream>
#include<netinet/in.h>
/*
class Acceptor
{
private:
    typedef std::function<void ()> newConCallBack;
    EventLoop* loopPtr;
    int socketFd;
    Channel* socketChannel;
    newConCallBack newConnectionCallBack;
    bool listenningSig;
public:
    Acceptor(EventLoop* lp);
    void setNewConnectionCallBack(const newConCallBack& cb);
    bool isListenning();
    void listen();
    void handleRead();
};
*/
Acceptor::Acceptor(EventLoop* lp ,int sockfd) : loopPtr(lp),
                                                socketFd(sockfd),
                                                socketChannel(new Channel(socketFd, loopPtr)),
                                                listenningSig(0)
{
    socketChannel->setReadCallBack(std::bind(&Acceptor::handleRead, this));
}

void Acceptor::setNewConnectionCallBack(const newConCallBack& cb)
{
    newConnectionCallBack = cb;
}

bool Acceptor::isListenning()
{
    return listenningSig == 1;
}

void Acceptor::listen()
{
    //传入acceptor的sockfd套解字是一个普通套解字。未经listen函数转换成为监听套解字
    //使用listen函数转换成监听套解字后，内核就会监听该套解字上的连接。
    //如果，不经转换，即使将套机子对应的cahnnle加入epoll，epoll也不会返回，因为内核不会通知任何关于该套解字的链接请球
    listenningSig = 1;
    ::listen(socketFd, 10);
    socketChannel->enableRead();
    std::cout << "listen\n";
}

void Acceptor::handleRead()
{
    struct sockaddr_in cliaddr;
    socklen_t addrlen;
    int conn = accept(socketFd, (struct sockaddr*)&cliaddr, &addrlen);
    if(newConnectionCallBack)
        newConnectionCallBack(conn, cliaddr);
}

