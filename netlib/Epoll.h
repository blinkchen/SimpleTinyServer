//
// Created by 陈希 on 2018/4/2.
//

#ifndef SIMPLETINYSERVER_EPOLL_H
#define SIMPLETINYSERVER_EPOLL_H

#include <sys/epoll.h>
#include <vector>
#include <unistd.h>
#include <cassert>

class Epoll {
public:
    explicit Epoll(int maxfds = 0, bool ET = false);
    virtual ~Epoll();
    void add(int fd, uint32_t event);
    void del(int fd, uint32_t event);
    void mod(int fd, uint32_t event);
    int wait(int timeout);
    const struct epoll_event* getEvents(){return _events;}

private:
    int _maxfds;
    bool _et;
    int _epfd;
    struct epoll_event* _events;
};


#endif //SIMPLETINYSERVER_EPOLL_H
