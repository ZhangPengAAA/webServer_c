#include<sys/socket.h>
#include<functional>

class EventLoop;
class Channel;

class Acceptor
{
private:
    typedef std::function<void (int,struct sockaddr_in)> newConCallBack;
    EventLoop* loopPtr;
    int socketFd;
    Channel* socketChannel;
    newConCallBack newConnectionCallBack;
    bool listenningSig;
public:
    Acceptor(EventLoop* lp ,int sockfd);
    void setNewConnectionCallBack(const newConCallBack& cb);
    bool isListenning();
    void listen();
    void handleRead();//当新的连接请求到来时，调用这个函数来处理。
                        //因而需要将这个函数注册到socketchannel的readcallback中
                        //实现，连接请求到来就自动建立连接。
};
