#pragma once

#include <memory>
#include <atomic>

#include <unithread/mutex.hpp>
#include <unithread/thread.hpp>

#include <colors/ColorModels.hpp>
#include <model/color_sample_provider.hpp>
#include <hal/rgb_strip.hpp>

namespace Unicorn { namespace Core
{
    class Renderer
    {
    public:
        using ColorSampleProviderPtr = std::shared_ptr<Model::IColorSampleProvider>;
        using RgbStripPtr = std::shared_ptr<Hal::RGBStrip>;

    public:
        Renderer(ColorSampleProviderPtr colorSampleProvider, RgbStripPtr rgbStrip);
        ~Renderer();

    public:
        void Start();
        void Stop();

        void SetBrightness(uint8_t brightness);

    private:
        void OnThreadExecute();

    private:
        ColorSampleProviderPtr colorSampleProvider_;
        RgbStripPtr rgbStrip_;

    private:
        Unithread::Thread thread_;
        Unithread::Mutex threadMutex_;
        std::atomic_bool continueWork_;
        std::atomic_uint_fast8_t brightness_;
    };
}}