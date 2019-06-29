#include <hal/rgb_strip.hpp>

#include <limits>

#include <driver/pwm.h>
#include <driver/gpio.h>

using namespace Unicorn::Hal;

namespace
{
    enum : size_t
    {
        CHANNEL_RED = 0,
        CHANNEL_GREEN = 1,
        CHANNEL_BLUE = 2,
    };

    constexpr size_t CHANNELS_COUNT = 3;
    constexpr gpio_num_t COLOR_PIN[CHANNELS_COUNT] = { GPIO_NUM_12, GPIO_NUM_14, GPIO_NUM_13 };

    constexpr uint16_t PWM_CHANNELS_MASK = 0x07;
    const uint32_t PWM_PERIOD = 5000;

    void ConfigurePWM()
    {
        const uint32_t channels[CHANNELS_COUNT] = {
            COLOR_PIN[CHANNEL_RED],
            COLOR_PIN[CHANNEL_GREEN],
            COLOR_PIN[CHANNEL_BLUE]
        };
        static uint32_t duties[] = { 0, 0, 0 };
        static int16_t phases[] = { 0, 0, 0 };

        pwm_init(PWM_PERIOD, duties, CHANNELS_COUNT, channels);

        pwm_set_channel_invert(PWM_CHANNELS_MASK);
        pwm_set_phases(phases);

        pwm_start();
    }

    uint32_t CalculateDuty(uint8_t color)
    {
        // Proportion calculations without float redundant arithmetic
        return (PWM_PERIOD * color) / std::numeric_limits<uint8_t>::max();
    }
}

RGBStrip::RGBStrip()
{
    ConfigurePWM();
}

void RGBStrip::ChangeColor(uint8_t r, uint8_t g, uint8_t b)
{
    pwm_set_duty(CHANNEL_RED, CalculateDuty(r));
    pwm_set_duty(CHANNEL_GREEN, CalculateDuty(g));
    pwm_set_duty(CHANNEL_BLUE, CalculateDuty(b));

    pwm_start();
}
