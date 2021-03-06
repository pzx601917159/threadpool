/*********************************************************************
	> File Name: main.cpp
	> Author: 彭治湘
	> Mail: 345109788@qq.com 
	> Created Time: Thursday 31 December 2015 01:55:04 PM CST
 ********************************************************************/
#include "threadpool.h"
#include "task.h"
#include <unistd.h>
int main()
{
    //创建10个线程
    ThreadPool threadpool(10);
    threadpool.Init();

    //插入任务
    Task* task = new Task();
    threadpool.AddTask(task);

    sleep(1); 
    //停止
    threadpool.Stop();
    return 0;
}

