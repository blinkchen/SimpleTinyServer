//
// Created by 陈希 on 2018/4/2.
//

#ifndef SIMPLETINYSERVER_CHANNEL_H
#define SIMPLETINYSERVER_CHANNEL_H

#include <functional>
typedef std::function<void()> EventCallback;

class EventLoop;
class Channel {
public:
    Channel(int fd=0, EventLoop* loop = 0)
            :_fd(fd),_index(-1),_loop(loop),_events(0),_revents(0)
    {}
    virtual ~Channel(){}


    //register callback
    void setReadCallback(const EventCallback &callback){_readcallback = callback;}
    void setWriteCallback(const EventCallback &callback){_writecallback = callback;}
    void setCloseCallback(const EventCallback &callback){_closecallback = callback;}
    void setErrorCallback(const EventCallback &callback){_errorcallback = callback;}

    //
    void setInterestedInRead(bool on);
    void setInterestedInWrite(bool on);
    void update();

    void handleEvent();

    //set
    void setFd(int fd){_fd = fd;}
    void setIndex(int index){_index = index;}
    void setLoop(EventLoop* loop){_loop = loop;}
    void setEvents(int events){_events |= events;}
    void setRevents(int revents){_revents |= revents;}
    //get
    int getFd(){return _fd;}
    int getIndex(){return _index;}
    EventLoop* getLoop() {return _loop;}
    int getEvents(){return _events;}
    int getRevents(){return _revents;}
private:
    int _fd;
    int _index;
    EventLoop* _loop;
    int _events;
    int _revents;

    EventCallback _readcallback,_writecallback,_closecallback,_errorcallback;



};


#endif //SIMPLETINYSERVER_CHANNEL_H
