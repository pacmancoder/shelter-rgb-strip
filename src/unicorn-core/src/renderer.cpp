#include <core/renderer.hpp>

#include <chrono>

using namespace Unicorn::Model;
using namespace Unicorn::Core;

using namespace Unithread;

namespace
{
    uint8_t Percentage(uint8_t value, uint8_t percentage)
    {
        return static_cast<uint8_t>(value * percentage / 255.f);
    }
}

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
        auto startTimestamp = std::chrono::system_clock::now();
        {
            auto lock = threadMutex_.ScopedLock();
            colorSampleProvider_->NextSample().on<Colors::RgbInt24Bit>(
                [this](const Colors::RgbInt24Bit& value)
                {
                    rgbStrip_->ChangeColor(
                        Percentage(value.r, static_cast<uint8_t>(brightness_)),
                        Percentage(value.g, static_cast<uint8_t>(brightness_)),
                        Percentage(value.b, static_cast<uint8_t>(brightness_))
                    );
                }
            );
        }
        Thread::SleepMs(20);

        auto timeDifference = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - startTimestamp
        );

        colorSampleProvider_->Process(static_cast<uint32_t>(timeDifference.count()));
    }
}

void Renderer::SetBrightness(uint8_t brightness)
{
    brightness_ = brightness;
}
