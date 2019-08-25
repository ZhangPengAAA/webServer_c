#include"Acceptor.h"
#include"TcpServer.h"
#include"EventLoop.h"
#include"EventLoopThreadPool.h"
#include"TcpConnection.h"

#include<sys/socket.h>
#include<netinet/in.h>
#include<functional>
#include<iostream>
#include<stdlib.h>
/*
class TcpServer
{
private:
    EventLoop* loopPtr;
    Acceptor* acp;
    int socketFd;
    std::string local;
    std::map<std::string, TcpConnection> connections;
public:
    TcpConnection(EventLoop* lp, struct sockaddr* addr);
    void start();
    void newConnection();
};
*/

TcpServer::TcpServer(EventLoop* lp, struct sockaddr_in* ad) : loopPtr(lp),
                                                             socketFd(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)),
                                                             acp(nullptr),
                                                             addr(ad),
                                                             tcpConNum(0),
                                                             local("none"),
                                                             pool(new EventLoopThreadPool(lp))
{
    bind(socketFd, (struct sockaddr*)addr, sizeof(*addr));
    acp = new Acceptor(lp, socketFd);
    acp->setNewConnectionCallBack(std::bind(&TcpServer::newConnection, this, std::placeholders::_1, std::placeholders::_2));
}

int TcpServer::getPoolSize(){return pool->getPoolSize(); }

void TcpServer::start()
{
    loopPtr->runInLoop(std::bind(&Acceptor::listen, acp));
}

void TcpServer::setThreadNum(int num)
{
    pool->createThread(num);
}

void TcpServer::newConnection(int conn, struct sockaddr_in cliaddr)
{
    std::cout << "newconnection arrived\n";
    std::cout << "connections now: " << connections.size() << "\n";
    EventLoop* lp = pool->getNextLoop();
    std::cout << "there\n";
    TcpConnection* tcptr = new TcpConnection(lp, conn, local, tcpConNum);
    connections[tcpConNum] = tcptr;
    tcptr->setMessageCallBack(messageCallBack);
    tcptr->setConnectionCallBack(connectionCallBack);
    tcptr->setCloseCallBack(std::bind(&TcpServer::removeConnection, this, std::placeholders::_1));
    lp->runInLoop(std::bind(&TcpConnection::connectEstablished, tcptr));
    ++tcpConNum;
}
void TcpServer::removeConnection(TcpConnection* tConn)
{
    loopPtr->runInLoop(std::bind(&TcpServer::removeConnectionInLoop, this, tConn));
}

void TcpServer::removeConnectionInLoop(TcpConnection* tConn)
{
    connections.erase(tConn->getNum());
    EventLoop* lp = tConn->getLoopPtr();
    lp->runInLoop(std::bind(&TcpConnection::finalRemoveConn, tConn));
    //delete tConn;
}
