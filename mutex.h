/*********************************************************************
	> File Name: lock.h
	> Author: 彭治湘
	> Mail: 345109788@qq.com 
	> Created Time: Thursday 31 December 2015 02:19:07 PM CST
 ********************************************************************/

#ifndef _MUTEX_H
#define _MUTEX_H
#include <pthread.h>
class Mutex
{
    public:
        void Lock();
        void UnLock();
        static Mutex* Instance();
        pthread_mutex_t* GetMutex();
    private:
        Mutex();
        ~Mutex();
        pthread_mutex_t m_lock;
        pthread_mutexattr_t m_attr;
};

class Cond
{
    public:
        void Broadcast();
        void Signal();
        void Wait(pthread_mutex_t* mutex);
        static Cond* Instance();
    private:
        Cond();
        ~Cond();
        pthread_cond_t m_cond;
};

#endif //_MUTEX_H
