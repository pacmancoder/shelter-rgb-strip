#include <iostream>
#include <cmath>

#include <esp_system.h>

#include <driver/pwm.h>
#include <driver/gpio.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <colors/ColorModels.hpp>

namespace
{
    const gpio_num_t PIN_COLOR[3] = { GPIO_NUM_12, GPIO_NUM_14, GPIO_NUM_13 };

    const uint32_t PWM_PERIOD = 5000;

    void ConfigurePWM()
    {
        static uint32_t duties[] = {0, 0, 0};
        static int16_t phases[] = {0, 0, 0};
        const uint32_t channels[] = {PIN_COLOR[0], PIN_COLOR[1], PIN_COLOR[2]};
        pwm_init(PWM_PERIOD, duties, 3, channels);
        pwm_set_channel_invert(0x07);
        pwm_set_phases(phases);
        pwm_start();
    }

}


extern "C" void app_main()
{
    ConfigurePWM();

    int step = 0;
    float brightness;
    for(;;)
    {
        brightness = std::abs((((step) % 256) - 128) / 128.0f);
        auto color = Colors::convert<Colors::RgbFloatNormalized>(
            Colors::HsvFloatNormalized {
                float(step % 360) / 360.0f,
                1.0,
                brightness / 4
            }
        );

        pwm_set_duty(0, static_cast<uint32_t>(PWM_PERIOD * color.r));
        pwm_set_duty(1, static_cast<uint32_t>(PWM_PERIOD * color.g));
        pwm_set_duty(2, static_cast<uint32_t>(PWM_PERIOD * color.b));

        pwm_start();

        ++step;
        vTaskDelay(10 / portTICK_RATE_MS);
    }
}