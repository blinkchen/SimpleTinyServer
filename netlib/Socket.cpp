//
// Created by 陈希 on 2018/4/2.
//

#include "Socket.h"

Socket::Socket() {
    _socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    assert(_socketfd > 0);
    SetNonBlock(_socketfd);
    SetCloseOnExec(_socketfd);
}

Socket::~Socket() {
    int ret = close(_socketfd);
    assert(ret >= 0);
}

void Socket::Bind(const struct sockaddr *serAddr) {
    int ret = bind(_socketfd, serAddr, sizeof(struct sockaddr_in));
    assert(ret >= 0);
}

void Socket::Listen() {
    int ret = listen(_socketfd, SOMAXCONN);
    assert(ret >= 0);
}

int Socket::Accept(struct sockaddr *cliAddr) {
    socklen_t socklen = sizeof(struct sockaddr);
    int connfd = accept(_socketfd, cliAddr, &socklen);
    assert(connfd > 0);
    SetNonBlock(connfd);
    SetCloseOnExec(connfd);
    return connfd;
}

int Socket::Connect(int socketfd, const struct sockaddr *serAddr) {
    int fd = connect(socketfd, serAddr, sizeof(struct sockaddr));
    assert(fd > 0);
    return fd;
}

//socket options
void SetNonBlock(int socketfd){
    int flags = fcntl(socketfd, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(socketfd, F_SETFL, flags);
}
void SetCloseOnExec(int socketfd){
    int flags = fcntl(socketfd, F_GETFL, 0);
    flags |= FD_CLOEXEC;
    fcntl(socketfd, F_SETFL, flags);
}


void Socket::setReuseAddr(bool on){
    int optval=on?1:0;
    setsockopt(_socketfd,SOL_SOCKET,SO_REUSEADDR,&optval,(socklen_t)sizeof optval);
}


void Socket::setReusePort(bool on) {
    int optval = on ? 1 : 0;
    setsockopt(_socketfd, SOL_SOCKET, SO_REUSEPORT, &optval, (socklen_t) sizeof optval);
}
//read and write
ssize_t Read(int socketfd,void *buf,size_t count){
    bzero(buf,count);
    return read(socketfd, buf, count);
}
ssize_t Write(int socketfd,const void* buf,size_t count){
    return write(socketfd, buf, count);
}