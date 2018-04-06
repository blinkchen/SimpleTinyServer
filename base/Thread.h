//
// Created by 陈希 on 2018/4/4.
//

#ifndef SIMPLETINYSERVER_THREAD_H
#define SIMPLETINYSERVER_THREAD_H


#include <functional>
#include <cassert>

class ThreadData{
public:
    explicit ThreadData(const std::function<void()>& function);
    virtual ~ThreadData(){}
    void run();

private:
    std::function<void()> _function;
};


class Thread {
public:
    explicit Thread(const std::function<void()>& function);
    virtual ~Thread();

    int run();
    int join();

    bool isRunning();
    pthread_t getTid();

private:
    std::function<void()> _function;
    bool _isRunning;
    bool _joined;
    pthread_t _tid;
    ThreadData* _data;
};


#endif //SIMPLETINYSERVER_THREAD_H
