//
// Created by 陈希 on 2018/4/2.
//

#include "Channel.h"
#include "EventLoop.h"
void Channel::update() {
    _loop->updateChannel(this);
}

void Channel::setInterestedInRead(bool on) {
    if (on)
        _events |= EPOLLIN;
    else
        _events &= ~EPOLLIN;
    update();
}

void Channel::setInterestedInWrite(bool on) {
    if (on)
        _events |= EPOLLOUT;
    else
        _events &= ~EPOLLOUT;
    update();
}

void Channel::handleEvent() {
    if (_revents&EPOLLHUP && !(_revents&EPOLLIN))
        if(_closecallback)
            _closecallback();
    if (_revents&EPOLLERR)
        if(_errorcallback)
            _errorcallback();
    if (_revents&EPOLLIN)
        if(_readcallback)
            _readcallback();
    if (_revents&EPOLLOUT)
        if(_writecallback)
            _writecallback();
}