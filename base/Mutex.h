//
// Created by 陈希 on 2018/4/4.
//

#ifndef SIMPLETINYSERVER_MUTEX_H
#define SIMPLETINYSERVER_MUTEX_H


#include <pthread.h>
#include <cassert>

class Mutex {
public:
    Mutex();
    virtual ~Mutex();
    void lock();
    void trylock();
    void unlock();
    pthread_mutex_t* getMutex();

    Mutex(const Mutex&) = delete;
    Mutex(Mutex&&) = delete;
    Mutex&operator=(const Mutex&) = delete;
    Mutex&operator=(Mutex&&) = delete;


private:
    pthread_mutex_t _lock;
    volatile bool _islocked;
};


#endif //SIMPLETINYSERVER_MUTEX_H
