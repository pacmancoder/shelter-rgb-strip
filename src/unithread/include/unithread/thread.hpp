#pragma once

#include <functional>

#include <pthread.h>

namespace Unithread
{
    class Thread
    {
    public:
        using ThreadFunction = std::function<void()>;

    public:
        explicit Thread(ThreadFunction&& threadFunction);
        void Start();
        void Join();

    public:
        static void SleepMs(int delayMs);
        static void Yield();

    private:
        static void* OnThreadExecute(void* data);

    private:
        pthread_t thread_;
        ThreadFunction threadFunction_;
    };
}