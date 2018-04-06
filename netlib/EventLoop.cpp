//
// Created by 陈希 on 2018/4/2.
//

#include "EventLoop.h"
const int WAITTIME=10000;
const int NEW=-1;
const int ADDED=1;
const int DELED=2;
EventLoop::EventLoop(const std::shared_ptr<Epoll> &epoller)
    :_curChannel(NULL),_epoller(epoller),_quit(false)
{

}

void EventLoop::loop() {
    while (!_quit){
        _activeChannels.clear();
        int eventnum = _epoller->wait(WAITTIME);
        const struct epoll_event *events = _epoller->getEvents();
        for (int i = 0; i < eventnum; ++i) {
	    printf("%d被触发！！", events->data.fd);
            _curChannel = _channelMap[events->data.fd];
            _curChannel->setRevents(events->events);
            _curChannel->handleEvent();
        }
    }
}

void EventLoop::updateChannel(Channel* channel) {
    int fd = channel->getFd();
    int index = channel->getIndex();
    if(index==NEW||index==DELED){
        if(index==NEW){
            _channelMap[fd]=channel;//add the channel to map
        }else{

        }
        channel->setIndex(ADDED);
        _epoller->add(fd,channel->getEvents());
    }else{
        if(channel->getEvents()==0){//interested events is none,delete the fd in epoll
            _epoller->del(fd,0);
            channel->setIndex(DELED);
        }
        else {
            _epoller->mod(fd,channel->getEvents());
        }
    }
}

void EventLoop::removeChannel(Channel* channel) {
    _channelMap.erase(channel->getFd());
    if(channel->getIndex()==ADDED){
        _epoller->del(channel->getFd(),0);
    }
    channel->setIndex(NEW);
}

bool EventLoop::hasChannel(Channel *channel) {
    return _channelMap.find(channel->getFd())!=_channelMap.end();
}
