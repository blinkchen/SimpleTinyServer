//
// Created by 陈希 on 2018/4/2.
//

#ifndef SIMPLETINYSERVER_SOCKET_H
#define SIMPLETINYSERVER_SOCKET_H

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <cassert>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>
#include <string.h>


class Socket {
public:
    Socket();
    virtual ~Socket();
    //Server
    void Bind(const struct sockaddr* serAddr);
    void Listen();
    int Accept(struct sockaddr* cliAddr);
    //Client
    int Connect(int socketfd, const struct sockaddr* serAddr);

    int getSocketfd(){return _socketfd;}

    void setReuseAddr(bool);
    void setReusePort(bool);

private:
    int _socketfd;
};


//socket options
void SetNonBlock(int socketfd);
void SetCloseOnExec(int socketfd);

//read and write
ssize_t Read(int socketfd,void *buf,size_t count);
ssize_t ReadAll(int socketfd,void *buf,size_t count);

ssize_t Write(int socketfd,const void* buf,size_t count);
ssize_t WriteAll(int socketfd,const void* buf,size_t count);



#endif //SIMPLETINYSERVER_SOCKET_H
