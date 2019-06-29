#include <unithread/mutex.hpp>

Unithread::Mutex::LockGuard::LockGuard(Unithread::Mutex& mutex)
    : parent_(mutex)
{
    parent_.Lock();
}

Unithread::Mutex::LockGuard::~LockGuard()
{
    parent_.Unlock();
}


Unithread::Mutex::Mutex()
    : mutex_(0)
{
    pthread_mutex_init(&mutex_, nullptr);
}

Unithread::Mutex::LockGuard Unithread::Mutex::ScopedLock()
{
    return LockGuard(*this);
}

void Unithread::Mutex::Lock()
{
    pthread_mutex_lock(&mutex_);
}

void Unithread::Mutex::Unlock()
{
    pthread_mutex_unlock(&mutex_);
}

Unithread::Mutex::~Mutex()
{
    pthread_mutex_destroy(&mutex_);
}
