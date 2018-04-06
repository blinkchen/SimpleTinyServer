//
// Created by 陈希 on 2018/4/6.
//

#include "TcpServer.h"


TcpServer::TcpServer(const char *addr, const int port, EventLoop* eventLoop, ThreadPool* threadPool)
    :_addr((char*)addr),_port(port),_eventLoop(eventLoop),_threadPool(threadPool)
{
    init();
}

TcpServer::~TcpServer() {
    delete[] _socket;
    _socket = NULL;
}

void TcpServer::init() {
    _socket = new Socket();
    _socket->setReuseAddr(true);
    _socket->setReusePort(true);

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(_addr);
    serverAddr.sin_port = htons(_port);
    _socket->Bind((const struct sockaddr*)&serverAddr);
}

void TcpServer::run(std::function<void()> listenCallback) {
    _socket->Listen();
    channel.setFd(_socket->getSocketfd());
    channel.setLoop(_eventLoop);
    channel.setInterestedInRead(true);
    channel.setReadCallback(listenCallback);
}
void TcpServer::accept(){
    struct sockaddr_in clientAddr;
    int clientSocket = _socket->Accept((struct sockaddr*)&clientAddr);
    cout << "新连接:" << clientSocket << " ";
    cout << "地址：" << inet_ntoa(clientAddr.sin_addr) << " ";
    cout << "端口号:" << ntohs(clientAddr.sin_port) << endl;
    SetNonBlock(clientSocket);
    Channel *channel = new Channel();
    channel->setFd(clientSocket);
    channel->setLoop(_eventLoop);
    channel->setInterestedInRead(true);
    channel->setReadCallback([=](){
        char buf[11];
        cout << channel->getFd() << "发来消息" ;
        Read(channel->getFd(),buf,11);
        buf[11] = '\0';
        printf("%s",buf);
        _threadPool->addTask(Task([=](){
            sleep(2);
	    channel->setInterestedInWrite(true);
            channel->setWriteCallback([=](){
                char buf[11] = "helloworld";
                Write(channel->getFd(),buf,11);
                buf[11] = '\0';
                printf("发送消息%s\n",buf);
		channel->setInterestedInWrite(false);
            });
        }));
    });

}
