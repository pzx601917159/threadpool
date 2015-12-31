/*********************************************************************
	> File Name: threadpool.h
	> Author: 彭治湘
	> Mail: 345109788@qq.com 
	> Created Time: Thursday 31 December 2015 12:15:23 PM CST
 ********************************************************************/

#include "threadpool.h"
#include "task.h"
#include "mutex.h"

//构造
ThreadPool::ThreadPool(uint32_t size)
{
    m_state = false;
    m_size = size;
    m_lock = Mutex::Instance();
}

//析构
ThreadPool::~ThreadPool()
{
}

//创建线程
bool ThreadPool::Init()
{
    m_state = true;
    //初始化互斥量
    for(int i = 0; i < m_size; i++)
    {
        pthread_t tid;
        //创建线程
        pthread_create(&tid, NULL, StartThread, (void*)this);
        //记录先策划那个id
        m_threads.push_back(tid);
    }
}

//开始
bool ThreadPool::Start()
{
    m_state = true;
}

//停止
bool ThreadPool::Stop()
{
    m_state = false;
    //等待线程的结束
    std::vector<pthread_t>::iterator it = m_threads.begin();
    while(it != m_threads.end())
    {
        pthread_join(*it++,NULL);
    }
    //清楚剩余的任务
    //判断之前一定要先加锁
    m_lock->Lock();
    while(!m_tasks.empty())
    {
       delete m_tasks.front();
       m_tasks.pop();
    }
    m_lock->UnLock();
    return true;
}

//插入任务
bool ThreadPool::AddTask(Task* task)
{
    m_tasks.push(task);
}

//线程函数
void* ThreadPool::StartThread(void* arg)
{
    ThreadPool* tp = (ThreadPool*)arg;
    tp->Run();
}

void ThreadPool::Run()
{
    while(m_state)
    {
        //取任务之前加锁，如果无法枷锁就阻塞在这里了,这样不好,可以优化为睡眠，使用条件变量唤醒
        Task* task;
        m_lock->Lock();
        if(!m_tasks.empty())
        {
            //取出任务
            Task *task = m_tasks.front();
            m_tasks.pop();

            //取了就解锁
            m_lock->UnLock();

            //执行任务
            task->OnTask();

            //执行完成之后删除
            delete task;
        }
        else
        {
            m_lock->UnLock();
        }
    }
}



