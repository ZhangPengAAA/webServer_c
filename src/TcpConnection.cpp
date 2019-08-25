#include"TcpConnection.h"
#include"EventLoop.h"
#include"Channel.h"

#include<functional>
#include<unistd.h>
#include<cstring>
#include<sys/socket.h>
#include<iostream>
/*
class TcpConnection
{
private:
    typedef std::function<void()> callBack;
    EventLoop* loopPtr;
    std::string name;
    int conn;
    Channel* connChannel;
    callBack messageCallBack, connectionCallBack, closeCallBack;
public:
    TcpConnection(EventLoop* lp, std::string& nam);
    void connectEstablished();
    void handleRead();
    void send();
    void handleWrite();
    void connectDestroyed();
    void shutdown();
};
*/

TcpConnection::TcpConnection(EventLoop* lp, int con, std::string& nam, int num) : loopPtr(lp),
                                                                conn(con),
                                                                name(nam),
                                                                connChannel(new Channel(conn, lp)),
                                                                number(num)
{
    connChannel->setReadCallBack(std::bind(&TcpConnection::handleRead, this));
}

void TcpConnection::connectEstablished()
{
    std::cout << "new connectionEstablished\n";
    connChannel->enableRead();
    if(connectionCallBack)
        connectionCallBack();
}

void TcpConnection::handleRead()
{
    char buf[1000] = {0}; int n;
    if((n = read(conn, buf, 1000)) < 0)
        return;
    if(n == 0){
        std::cout << "connection closed\n";
        handleClose();
    }else if(messageCallBack){
         messageCallBack(buf, strlen(buf), conn);
         shutdown(conn, SHUT_WR);
         read(conn, buf, 10000);
         std::cout << buf <<std::endl;
         close(conn);
         handleClose();
    }
}

void TcpConnection::handleClose()
{
    connChannel->disable();
    closeCallBack(this);
    //loopPtr->runInLoop(std::bind(&EventLoop::removeChannel, loopPtr, connChannel));//移除本tcpconnection所属loop线程中的本channel
    //在tcpserver中移除tcpConnection
}

void TcpConnection::finalRemoveConn()
{
    loopPtr->runInLoop(std::bind(&EventLoop::removeChannel, loopPtr, connChannel));
}



