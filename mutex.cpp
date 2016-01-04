/*********************************************************************
	> File Name: lock.h
	> Author: 彭治湘
	> Mail: 345109788@qq.com 
	> Created Time: Thursday 31 December 2015 02:19:07 PM CST
 ********************************************************************/
#include "mutex.h"
#include <iostream>

void Mutex::Lock()
{
    pthread_mutex_lock(&m_lock);
}

void Mutex::UnLock()
{
    pthread_mutex_unlock(&m_lock);
}

Mutex* Mutex::Instance()
{
    static Mutex mutex;
    return &mutex;
}

//设置了递归的属性，其实也可以不设置
Mutex::Mutex()
{
    pthread_mutexattr_init(&m_attr);
    //pthread_mutexattr_settype(&m_attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&m_lock,&m_attr);
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&m_lock);
    pthread_mutexattr_destroy(&m_attr);
}

pthread_mutex_t* Mutex::GetMutex()
{
    return &m_lock;
}

Cond::Cond()
{
    pthread_cond_init(&m_cond, NULL);
}

Cond::~Cond()
{
    pthread_cond_destroy(&m_cond);
}

Cond* Cond::Instance()
{
    static Cond cond;
    return &cond;
}

void Cond::Signal()
{
    pthread_cond_signal(&m_cond);
}

void Cond::Broadcast()
{
    pthread_cond_broadcast(&m_cond);
}


void Cond::Wait(pthread_mutex_t* mutex)
{
    pthread_cond_wait(&m_cond,mutex);
}

