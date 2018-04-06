//
// Created by 陈希 on 2018/4/4.
//

#include "ThreadPool.h"


ThreadPool::ThreadPool(int poolsize)
        : _poolsize(poolsize),
          _taskcon(_taskmutex) {
    init();
}

int ThreadPool::init() {
    _poolstate = STARTED;
    _threadVec.reserve(_poolsize);
    for (int i = 0; i < _poolsize; ++i) {
        Thread thread(std::bind(&ThreadPool::workerThread, this));

        _threadVec.push_back(thread);
        _threadVec.back().run();
    }
}

ThreadPool::~ThreadPool() {
    if (_poolstate != STOPPED) {
        destroy();
    }
}

void ThreadPool::destroy() {
    _taskmutex.lock();
    _poolstate = STOPPED;
    _taskmutex.unlock();

    _taskcon.wakeAll();

    int ret;
    for (int i = 0; i < _poolsize; ++i) {
        ret = _threadVec[i].join();
    }
}

int ThreadPool::addTask(const Task &task) {
    _taskmutex.lock();
    _tasks.push_back(task);
    _taskcon.wakeOne();
    _taskmutex.unlock();
    return 0;
}

void ThreadPool::workerThread() {
    while (_poolstate == STARTED) {
        _taskmutex.lock();
        while ((_poolstate == STARTED) && (_tasks.empty())) {
            _taskcon.wait();
        }

        if (_poolstate == STOPPED) {
            _taskmutex.unlock();
            pthread_exit(NULL);
        }

        Task task = _tasks.front();
        _tasks.pop_front();
        _taskmutex.unlock();

        task.run();
    }
}

