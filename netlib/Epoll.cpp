//
// Created by 陈希 on 2018/4/2.
//

#include "Epoll.h"

Epoll::Epoll(int maxfds, bool ET)
    :_maxfds(maxfds),_et(ET)
{
    _events = new struct epoll_event[_maxfds];
    _epfd = epoll_create(_maxfds);
    assert(_epfd > 0);
}

Epoll::~Epoll() {
    delete[] _events;
    int ret = close(_epfd);
    assert(ret > 0);
}

void Epoll::add(int fd,uint32_t event){
    struct epoll_event ev;
    ev.data.fd=fd;
    if(_et)
        ev.events=event|EPOLLET;
    else
        ev.events=event;
    epoll_ctl(_epfd,EPOLL_CTL_ADD,fd,&ev);
}

void Epoll::del(int fd,uint32_t event){
    struct epoll_event ev;
    ev.data.fd=fd;
    if(_et)
        ev.events=event;
    else
        ev.events=event;
    epoll_ctl(_epfd,EPOLL_CTL_DEL,fd,&ev);

}

void Epoll::mod(int fd,uint32_t event){
    struct epoll_event ev;
    ev.data.fd=fd;
    if(_et)
        ev.events=event|EPOLLET;
    else
        ev.events=event;
    epoll_ctl(_epfd,EPOLL_CTL_MOD,fd,&ev);
}
int Epoll::wait(int timeout){
    return epoll_wait(_epfd,_events,_maxfds,timeout);
}
