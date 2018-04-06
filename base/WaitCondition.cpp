//
// Created by 陈希 on 2018/4/4.
//

#include "WaitCondition.h"

WaitCondition::WaitCondition(Mutex &mutex)
    :_mutex(mutex)
{
    int ret = pthread_cond_init(&_cond, NULL);
    assert(ret == 0);
}

WaitCondition::~WaitCondition() {
    int ret = pthread_cond_destroy(&_cond);
    assert(ret == 0);
}

void WaitCondition::wait() {
    int ret = pthread_cond_wait(&_cond, _mutex.getMutex());
}

bool WaitCondition::waitTime(long seconds, long nanoseconds) {
    timespec now;
    clock_gettime(CLOCK_REALTIME,&now);
    const timespec timeout{now.tv_sec+(time_t)seconds,now.tv_nsec+nanoseconds};
    return ETIMEDOUT == pthread_cond_timedwait(&_cond,_mutex.getMutex(),&timeout);
}

void WaitCondition::wakeOne() {
    int ret = pthread_cond_signal(&_cond);
    assert(ret == 0);
}

void WaitCondition::wakeAll() {
    int ret = pthread_cond_broadcast(&_cond);
    assert(ret == 0);
}