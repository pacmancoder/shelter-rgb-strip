#include <unithread/thread.hpp>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

Unithread::Thread::Thread(Unithread::Thread::ThreadFunction&& threadFunction)
    : thread_(0)
    , threadFunction_(std::move(threadFunction)) {}

void Unithread::Thread::Start()
{
    pthread_create(&thread_, nullptr, Thread::OnThreadExecute, static_cast<void*>(this));
}

void Unithread::Thread::Join()
{
    pthread_join(thread_, nullptr);
    thread_ = 0;
}

void* Unithread::Thread::OnThreadExecute(void* data)
{
    auto* thread = reinterpret_cast<Unithread::Thread*>(data);
    thread->threadFunction_();
    return nullptr;
}

void Unithread::Thread::SleepMs(int delayMs)
{
    vTaskDelay(delayMs / portTICK_RATE_MS);
}

void Unithread::Thread::Yield()
{
    taskYIELD();
}
