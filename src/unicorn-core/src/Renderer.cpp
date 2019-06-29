#include <core/Renderer.hpp>

using namespace Unicorn::Model;
using namespace Unicorn::Core;

using namespace Unithread;

Renderer::Renderer(Renderer::ColorSampleProviderPtr colorSampleProvider, RgbStripPtr rgbStrip)
    : colorSampleProvider_(std::move(colorSampleProvider))
    , rgbStrip_(std::move(rgbStrip))
    , thread_(std::bind(&Renderer::OnThreadExecute, this))
    , threadMutex_()
    , continueWork_(true)
{
    // Don't allow thread to continue it's work
    threadMutex_.Lock();
    thread_.Start();
}

Renderer::~Renderer()
{
    continueWork_ = false;
    thread_.Start();
    thread_.Join();
}

void Renderer::Start()
{
    threadMutex_.Unlock();
}

void Renderer::Stop()
{
    threadMutex_.Lock();
}

void Renderer::OnThreadExecute()
{
    while (continueWork_)
    {
        {
            auto lock = threadMutex_.ScopedLock();
            colorSampleProvider_->NextSample().on<Colors::RgbInt24Bit>(
                [this](const Colors::RgbInt24Bit& value)
                {
                    rgbStrip_->ChangeColor(value.r, value.g, value.b);
                }
            );
        }
        Thread::SleepMs(20);
    }
}
