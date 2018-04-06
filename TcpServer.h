//
// Created by 陈希 on 2018/4/6.
//

#ifndef SIMPLETINYSERVER_TCPSERVER_H
#define SIMPLETINYSERVER_TCPSERVER_H

#include <iostream>
#include "netlib/Socket.h"
#include "netlib/EventLoop.h"
#include "base/ThreadPool.h"
using namespace std;
class TcpServer {
public:
    TcpServer(const char* addr, const int port, EventLoop* eventLoop, ThreadPool* threadPool);
    virtual ~TcpServer();
    void run(std::function<void()> listencallback);
    void accept();

private:
    void init();


private:
    char* _addr;
    int _port;
    Socket* _socket;
    EventLoop* _eventLoop;
    Channel channel;
    ThreadPool* _threadPool;
};


#endif //SIMPLETINYSERVER_TCPSERVER_H
