#include <iostream>

#include "netlib/Channel.h"
#include "base/ThreadPool.h"
#include "TcpServer.h"

using namespace std;

const char* SERVER_IP = "0.0.0.0";
const int SERVER_PORT = 6666;

/*
int main() {
    Socket serverSocket;
    int sockfd = serverSocket.getSocketfd();
    serverSocket.setReusePort(true);
    serverSocket.setReuseAddr(true);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(6666);
    serverSocket.Bind((const struct sockaddr*)&serverAddr);
    serverSocket.Listen();

    struct sockaddr_in clientAddr;
    while(1) {
        int clientSocket = serverSocket.Accept((struct sockaddr *) &clientAddr);
        cout << "新连接:" << clientSocket << endl;
        cout << "地址：" << inet_ntoa(clientAddr.sin_addr) << endl;
        cout << "端口号:" << ntohs(clientAddr.sin_port) << endl;
        close(clientSocket);
    }

    return 0;
}
 */



int main() {
    std::shared_ptr<Epoll> poller=std::make_shared<Epoll>(1024, true);
    EventLoop eventloop(poller);
    ThreadPool threadPool(4);
    TcpServer tcpServer(SERVER_IP,SERVER_PORT,&eventloop,&threadPool);
    tcpServer.run([&](){
        tcpServer.accept();
    });
    eventloop.loop();
}
