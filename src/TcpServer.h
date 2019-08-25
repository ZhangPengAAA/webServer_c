#include<map>
#include<string>
#include<sys/socket.h>
#include<functional>

class Acceptor;
class EventLoop;
class TcpConnection;
class EventLoopThreadPool;

class TcpServer
{
private:
    typedef std::function<void(char*, int, int)> callBack;
    typedef std::function<void()> connCallBack;
    callBack messageCallBack, closeCallBack;
    connCallBack connectionCallBack;

    EventLoopThreadPool* pool;
    EventLoop* loopPtr;
    Acceptor* acp;
    struct sockaddr_in* addr;
    int socketFd;
    int tcpConNum;
    std::string local;
    std::map<int, TcpConnection*> connections;
public:
    TcpServer(EventLoop* lp, struct sockaddr_in* addr);
    void start();
    void newConnection(int conn, struct sockaddr_in cliaddr);
    void setThreadNum(int num);
    int getPoolSize();//{return pool->getPoolSize(); }

    void setMessageCallBack(const callBack& cb)
    {
        messageCallBack = cb;
    }

    void setConnectionCallBack(const connCallBack& cb)
    {
        connectionCallBack = cb;
    }

    void removeConnection(TcpConnection* tConn);
    void removeConnectionInLoop(TcpConnection* tConn);
};
