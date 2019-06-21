#include <iostream>
#include <cmath>

#include <esp_system.h>

#include <driver/pwm.h>
#include <driver/gpio.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


namespace
{
    typedef struct {
        double r;       // a fraction between 0 and 1
        double g;       // a fraction between 0 and 1
        double b;       // a fraction between 0 and 1
    } rgb;

    typedef struct {
        double h;       // angle in degrees
        double s;       // a fraction between 0 and 1
        double v;       // a fraction between 0 and 1
    } hsv;

    rgb hsv2rgb(hsv in)
    {
        double      hh, p, q, t, ff;
        long        i;
        rgb         out;

        if(in.s <= 0.0) {       // < is bogus, just shuts up warnings
            out.r = in.v;
            out.g = in.v;
            out.b = in.v;
            return out;
        }
        hh = in.h;
        if(hh >= 360.0) hh = 0.0;
        hh /= 60.0;
        i = (long)hh;
        ff = hh - i;
        p = in.v * (1.0 - in.s);
        q = in.v * (1.0 - (in.s * ff));
        t = in.v * (1.0 - (in.s * (1.0 - ff)));

        switch(i) {
            case 0:
                out.r = in.v;
                out.g = t;
                out.b = p;
                break;
            case 1:
                out.r = q;
                out.g = in.v;
                out.b = p;
                break;
            case 2:
                out.r = p;
                out.g = in.v;
                out.b = t;
                break;

            case 3:
                out.r = p;
                out.g = q;
                out.b = in.v;
                break;
            case 4:
                out.r = t;
                out.g = p;
                out.b = in.v;
                break;
            case 5:
            default:
                out.r = in.v;
                out.g = p;
                out.b = q;
                break;
        }
        return out;
    }


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
    double brightness;
    while (true)
    {
        brightness = std::abs((((step) % 256) - 128) / 128.0) / 4;
        auto color = hsv2rgb(hsv{ double(step % 360), 1.0, brightness });

        pwm_set_duty(0, static_cast<uint32_t>(PWM_PERIOD * color.r));
        pwm_set_duty(1, static_cast<uint32_t>(PWM_PERIOD * color.g));
        pwm_set_duty(2, static_cast<uint32_t>(PWM_PERIOD * color.b));
        pwm_start();

        ++step;
        vTaskDelay(10 / portTICK_RATE_MS);
    }
}