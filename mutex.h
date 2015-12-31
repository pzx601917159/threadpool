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
    private:
        Mutex();
        ~Mutex();
        pthread_mutex_t m_lock;
        pthread_mutexattr_t m_attr;
};

#endif //_MUTEX_H
