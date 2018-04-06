//
// Created by 陈希 on 2018/4/2.
//

#ifndef SIMPLETINYSERVER_EVENTLOOP_H
#define SIMPLETINYSERVER_EVENTLOOP_H

#include <functional>
#include <vector>
#include <unordered_map>
#include <memory>
#include "Channel.h"
#include "Epoll.h"

typedef std::function<void()> Func;

class EventLoop {
public:
    explicit EventLoop(){}
    explicit EventLoop(const std::shared_ptr<Epoll> &epoller);
    virtual ~EventLoop(){}

    void loop();
    void updateChannel(Channel* channel);
    void removeChannel(Channel* channel);
    bool hasChannel(Channel* channel);
private:
    std::vector<Channel*> _activeChannels;
    Channel* _curChannel{};
    std::shared_ptr<Epoll> _epoller;
    bool _quit;
    std::unordered_map<int, Channel*> _channelMap;
};


#endif //SIMPLETINYSERVER_EVENTLOOP_H
