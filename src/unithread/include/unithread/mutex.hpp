#pragma once

#include <pthread.h>

namespace Unithread
{
    class Mutex
    {
    public:
        class LockGuard
        {
        public:
            explicit LockGuard(Mutex& mutex);
            ~LockGuard();

        private:
            Mutex& parent_;
        };

    public:
        friend class LockGuard;

    public:
        Mutex();
        ~Mutex();

    public:
        LockGuard ScopedLock();

        void Lock();
        void Unlock();

    private:
        pthread_mutex_t mutex_;
    };
}