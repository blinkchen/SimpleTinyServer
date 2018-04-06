//
// Created by 陈希 on 2018/4/4.
//

#include "Task.h"

Task::Task(const std::function<void()> &function)
    :_function(function)
{

}

Task::~Task() {

}

void Task::run() {
    _function();
}
