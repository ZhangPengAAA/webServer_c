#pragma once
#include<sys/socket.h>
class EventLoop;

class EventLoopThread
{
private:
    EventLoop* loopPtr;
    pthread_t threadID;

public:
    EventLoopThread();
    void start();
    //static void* pthreadFunc(void *arg);
    EventLoop* getLoop();
    void setLoop(EventLoop* lptr);
    pthread_t getPthreadId() { return threadID; }
};
