#include<pthread.h>
#include"EventLoop.h"
#include"EventLoopThread.h"
#include<iostream>
#include<unistd.h>

void* pthreadFunc(void * arg)
{
    EventLoop* lp = new EventLoop();
    EventLoopThread* ptr = (EventLoopThread*) arg;
    ptr->setLoop(lp);
    ptr->start();
}




EventLoopThread::EventLoopThread() : loopPtr(nullptr)//,threadID(0)
{
    int i = 0;
    i = pthread_create(&threadID, nullptr, pthreadFunc, (void*)this);
    std::cout << "threadid: " << threadID << "\n";
}

void EventLoopThread::start()
{
    std::cout << "start\n";
    loopPtr->loop();
}

void EventLoopThread::setLoop(EventLoop* lptr)
{
    loopPtr = lptr;
}

EventLoop* EventLoopThread::getLoop()
{
    return loopPtr;
}





