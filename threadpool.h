/*********************************************************************
	> File Name: threadpool.h
	> Author: 彭治湘
	> Mail: 345109788@qq.com 
	> Created Time: Thursday 31 December 2015 12:15:23 PM CST
 ********************************************************************/

#ifndef _THREADPOOL_H
#define _THREADPOOL_H

#include <inttypes.h>
#include <pthread.h>
#include <queue>
#include <vector>

class Task;
class Mutex;
class Cond;

class ThreadPool
{
    public:
    //构造
    ThreadPool(uint32_t size);
    //析构
    ~ThreadPool();
    //创建线程
    bool Init();
    //开始
    bool Start();
    //停止
    bool Stop();
    //插入任务
    bool AddTask(Task* task);

    //线程函数
    static void* StartThread(void* arg);
    
    //线程执行的函数
    void Run();

    private:
    std::queue<Task*> m_tasks;          //任务列表
    std::vector<pthread_t> m_threads;   //线程池
    volatile bool m_state;              //线程池状态
    uint32_t m_size;                    //线程池大小
    Mutex* m_lock;            //线程池中的锁
    Cond* m_cond;
};

#endif //_THREADPOOL_H
