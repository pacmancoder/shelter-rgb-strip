#include <array>

#include <mgos.h>

namespace
{
    using GpioPinId = int;

    // Inversed signaling
    const bool PIN_VALUE_COLOR_ENABLE = false;
    const bool PIN_VALUE_COLOR_DISABLE = true;

    const GpioPinId PIN_RED = 14;
    const GpioPinId PIN_GREEN = 12;
    const GpioPinId PIN_BLUE = 13;

    const std::array<GpioPinId, 3> RGB_STRIP_PINS = { PIN_RED, PIN_GREEN, PIN_BLUE };

    int COLOR_SWITCH_INTERVAL_MS = 100;

    extern "C" void on_color_switch(void*)
    {
        static int i = 0;

        for(auto pin : RGB_STRIP_PINS)
        {
            mgos_gpio_write(pin, PIN_VALUE_COLOR_DISABLE);
        }

        mgos_gpio_write(RGB_STRIP_PINS[i % RGB_STRIP_PINS.size()], PIN_VALUE_COLOR_ENABLE);

        ++i;
    }
}

extern "C" mgos_app_init_result mgos_app_init() 
{
    for (auto pin : RGB_STRIP_PINS)
    { 
        mgos_gpio_setup_output(pin, PIN_VALUE_COLOR_DISABLE);
        mgos_gpio_set_mode(pin, MGOS_GPIO_MODE_OUTPUT);
    }
    
    mgos_set_timer(COLOR_SWITCH_INTERVAL_MS, MGOS_TIMER_REPEAT, on_color_switch, nullptr); 

    return MGOS_APP_INIT_SUCCESS;
}
