//
// Created by 陈希 on 2018/4/4.
//

#ifndef SIMPLETINYSERVER_THREADPOOL_H
#define SIMPLETINYSERVER_THREADPOOL_H

#include <vector>
#include <deque>
#include <functional>
#include "Task.h"
#include "Mutex.h"
#include "WaitCondition.h"
#include "Thread.h"

const int STARTED = 0;
const int STOPPED = 1;
#define DEFAULT_POOL_SIZE 10

class ThreadPool {
public:
    ThreadPool(int poolsize=DEFAULT_POOL_SIZE);

    virtual ~ThreadPool();

    void destroy();

    void workerThread();

    int addTask(const Task& task);

private:
    int init();

private:
    int _poolsize;
    Mutex _taskmutex;
    WaitCondition _taskcon;

    std::vector<Thread> _threadVec;
    std::deque<Task> _tasks;
    volatile int _poolstate;

};


#endif //SIMPLETINYSERVER_THREADPOOL_H
