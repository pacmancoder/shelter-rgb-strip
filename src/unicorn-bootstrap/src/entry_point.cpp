#include <memory>

#include <memory>
#include <random>

#include <unithread/thread.hpp>

#include <hal/device.hpp>

#include <core/renderer.hpp>
#include <core/shared_color_sample_provider.hpp>
#include <core/spectrum_color_sample_provider.hpp>
#include <core/breathing_color_sample_provider.hpp>
#include <core/static_color_sample_provider.hpp>

#include <shelter-utils/ssid_device_descriptor.hpp>

using namespace Unicorn;

namespace
{
    std::unique_ptr<Core::Renderer> renderer;
}

extern "C" void app_main()
{
    auto& device = Hal::Device::GetInstance();
    device.Init();

    device.GetWifi()->StartOpenAp(
        Shelter::Utils::EncodeDeviceDescriptorToSsid(Shelter::Model::DeviceDescriptor {
            Shelter::Model::ShelterVersion(1, 0, 0),
            Shelter::Model::Service(Shelter::Model::Service::Id::ConfigureSta),
            Shelter::Model::DeviceClass(Shelter::Model::DeviceClass::Id::RgbLedStrip),
            Shelter::Model::DeviceVendor(Shelter::Model::DeviceVendor::Id::IndividualPacmancoder),
            Shelter::Model::DeviceSerial(0x1122334455667788),
        }
    ));

    auto sharedSampleProvider = std::make_shared<Core::SharedColorSampleProvider>();

    renderer = std::make_unique<Core::Renderer>(sharedSampleProvider, device.GetRgbStrip());
    renderer->SetBrightness(64);
    renderer->Start();

    auto breathingSampleGenerator = std::make_shared<Core::BreathingColorSampleProvider>(
        0.25f,
        Colors::RgbInt24Bit { 255, 16, 255 }
    );

    sharedSampleProvider->SubstituteOriginal(breathingSampleGenerator);

    Unithread::Thread::SleepMs(5000);

    breathingSampleGenerator->SetColor(Colors::RgbInt24Bit { 32, 255, 64 });
    breathingSampleGenerator->SetSpeed(1.f);

    Unithread::Thread::SleepMs(5000);

    sharedSampleProvider->SubstituteOriginal(
        std::make_shared<Core::SpectrumColorSampleProvider>(
            0.25f
        ));

    auto rng = device.GetRng();
    std::uniform_int_distribution<uint8_t> colorGenerator(0, 255);
}