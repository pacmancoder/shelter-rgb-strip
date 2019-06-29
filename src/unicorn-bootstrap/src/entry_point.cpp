#include <memory>

#include <memory>
#include <random>

#include <unithread/thread.hpp>

#include <hal/device.hpp>

#include <core/Renderer.hpp>
#include <core/static_color_sample_provider.hpp>
#include <core/shared_color_sample_provider.hpp>

/*
 *         brightness = std::abs((((step) % 256) - 128) / 128.0f);
        auto color = Colors::convert<Colors::RgbFloatNormalized>(
            Colors::HsvFloatNormalized{
                float(step % 360) / 360.0f,
                1.0,
                brightness / 4
            }
        );
 */

using namespace Unicorn;

namespace
{
    std::unique_ptr<Core::Renderer> renderer;
}

extern "C" void app_main()
{
    auto& device = Hal::Device::GetInstance();
    device.Init();

    auto sharedSampleProvider = std::make_shared<Core::SharedColorSampleProvider>();

    sharedSampleProvider->SubstituteOriginal(std::make_shared<Core::StaticColorSampleProvider>(
        Colors::RgbInt24Bit{ 32, 32, 32 }
    ));

    renderer = std::make_unique<Core::Renderer>(sharedSampleProvider, device.GetRgbStrip());
    renderer->Start();

    auto rng = device.GetRng();
    std::uniform_int_distribution<uint8_t> colorGenerator(0, 255);

    // Test code
    for (;;)
    {
        sharedSampleProvider->SubstituteOriginal(std::make_shared<Core::StaticColorSampleProvider>(
            Colors::RgbInt24Bit {
                static_cast<uint8_t>(colorGenerator(*rng) % 256),
                static_cast<uint8_t>(colorGenerator(*rng) % 256),
                static_cast<uint8_t>(colorGenerator(*rng) % 256)
            }
        ));

        Unithread::Thread::SleepMs(500);
    }

}