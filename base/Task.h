//
// Created by 陈希 on 2018/4/4.
//

#ifndef SIMPLETINYSERVER_TASK_H
#define SIMPLETINYSERVER_TASK_H


#include <functional>

class Task {
public:
    explicit Task(const std::function<void()>&);
    virtual ~Task();

    void run();

private:
    std::function<void()> _function;
};


#endif //SIMPLETINYSERVER_TASK_H
