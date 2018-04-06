//
// Created by 陈希 on 2018/4/4.
//

#include "Thread.h"

ThreadData::ThreadData(const std::function<void()> &function)
    :_function(function)
{
}

void ThreadData::run() {
    _function();
}


void* startThread(void* arg){
    ThreadData* data = (ThreadData*)arg;
    data->run();
}

Thread::Thread(const std::function<void()> &function)
    :_function(function),_isRunning(false),_joined(false),_tid(0),_data(NULL)
{

}

Thread::~Thread() {
    if (_isRunning && ! _joined)
        pthread_detach(_tid);
    if (_data){
        delete _data;
        _data = NULL;
    }
}

int Thread::run() {
    assert(!_isRunning);
    _isRunning = true;
    _data = new ThreadData(_function);
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if ((pthread_create(&_tid, &attr, startThread, (void*)_data)) == 0)
        return 0;
    else{
        fprintf(stderr, "pthread_create\n");
        _isRunning= false;
        delete _data;
        _data = NULL;
        return -1;
    }
}

int Thread::join() {
    assert(_isRunning);
    assert(!_joined);
    _joined = true;
    return pthread_join(_tid, NULL);
}

bool Thread::isRunning() {
    return _isRunning;
}

pthread_t Thread::getTid() {
    return _tid;
}
