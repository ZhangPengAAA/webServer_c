#include<functional>
#include<string>

class EventLoop;
class Channel;

class TcpConnection
{
private:
    typedef std::function<void(char*, int, int)> callBack;
    typedef std::function<void()> connCallBack;
    typedef std::function<void(TcpConnection*)>  closeCall;
    EventLoop* loopPtr;
    std::string name;
    int number;
    int conn;
    Channel* connChannel;
    callBack messageCallBack;//, closeCallBack;
    connCallBack connectionCallBack;
    closeCall closeCallBack;
public:
    TcpConnection(EventLoop* lp, int con, std::string& nam, int num);
    void connectEstablished();
    void handleRead();
    void send();
    void handleWrite();
    void handleClose();
    void connectDestroyed();
    //void shutdown();
    void finalRemoveConn();

    void setMessageCallBack(const callBack& cb)
    {
        messageCallBack = cb;
    }

    void setConnectionCallBack(const connCallBack& cb)
    {
        connectionCallBack = cb;
    }

    void setCloseCallBack(const closeCall& cb)
    {
        closeCallBack = cb;
    }

    int getNum() { return number; }
    EventLoop* getLoopPtr() { return loopPtr; }
};
