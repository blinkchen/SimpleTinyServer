//
// Created by 陈希 on 2018/4/4.
//

#ifndef SIMPLETINYSERVER_WAITCONDITION_H
#define SIMPLETINYSERVER_WAITCONDITION_H

#include <errno.h>
#include "Mutex.h"

class WaitCondition {
public:
    explicit WaitCondition(Mutex&);
    virtual ~WaitCondition();

    void wait();
    bool waitTime(long seconds, long nanoseconds);
    void wakeOne();
    void wakeAll();

    WaitCondition(const WaitCondition&)=delete;
    WaitCondition(WaitCondition&&)=delete;
    WaitCondition& operator=(const WaitCondition&)=delete;
    WaitCondition& operator=(WaitCondition&&)=delete;

private:
    pthread_cond_t _cond;
    Mutex& _mutex;
};


#endif //SIMPLETINYSERVER_WAITCONDITION_H
