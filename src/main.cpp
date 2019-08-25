#include"EventLoop.h"
#include"Channel.h"
#include<unistd.h>
#include<sys/time.h>
#include<iostream>
#include<pthread.h>
#include<functional>
#include"EventLoopThread.h"
#include"EventLoopThreadPool.h"
#include"Acceptor.h"
#include<sys/socket.h>
#include<netinet/in.h>
#include"TcpServer.h"
#include"TcpConnection.h"
#include"httpHandler.h"
class EventLoopThread;

void messageCallBack(char* buf, int size)
{
    for(int i = 0; i < size; ++i)
        std::cout << buf[i] << " ";

}

void connectionCallBack()
{
    std::cout << "connectionCallback" << std::endl;
}

int main()
{
    /*
    EventLoop elp;
    //elp.loop();
    //int socketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind(socketFd, (struct sockaddr*)&addr, sizeof(addr));
    //listen(socketFd, 10);
    //accept(socketFd, nullptr, nullptr);
    TcpServer server(&elp, &addr);
    server.setMessageCallBack(std::bind(requestHandler,std::placeholders::_1,std::placeholders::_2, std::placeholders::_3));
    server.setConnectionCallBack(connectionCallBack);

    server.start();
    elp.loop();
    //cl.setReadCallBack(e);
    //cl.enableRead();
    std::cout << "aaa\n";
    //lp->runInLoop(e);//(std::bind(&EventLoop::loop, lp));
    sleep(10);
    */
    EventLoop elp;

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    TcpServer server(&elp, &addr);
    server.setThreadNum(100);
    server.setMessageCallBack(std::bind(requestHandler,std::placeholders::_1,std::placeholders::_2, std::placeholders::_3));
    server.setConnectionCallBack(connectionCallBack);

    server.start();
    elp.loop();



    sleep(10);
    return 0;
}
