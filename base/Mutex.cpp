//
// Created by 陈希 on 2018/4/4.
//

#include "Mutex.h"

Mutex::Mutex()
    :_islocked(false)
{
    int ret = pthread_mutex_init(&_lock,NULL);
    assert(ret == 0);
}

Mutex::~Mutex() {
    assert(_islocked== false);
    pthread_mutex_destroy(&_lock);
}

void Mutex::lock() {
    int ret = pthread_mutex_lock(&_lock);
    assert(ret == 0);
    _islocked = true;
}

void Mutex::trylock() {
    int ret = pthread_mutex_trylock(&_lock);
    assert(ret == 0);
    _islocked = true;
}

void Mutex::unlock() {
    int ret = pthread_mutex_unlock(&_lock);
    assert(ret == 0);
}

pthread_mutex_t *Mutex::getMutex() {
    return &_lock;
}
