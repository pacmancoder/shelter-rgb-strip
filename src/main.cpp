#include <mgos.h>
#include <mgos_pwm_rgb_led.h>

#include <array>
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>

namespace
{
    using GpioPinId = int;

    /// Inversed signaling
    const bool PIN_VALUE_COLOR_DISABLE = true;

    const GpioPinId PIN_RED = 14;
    const GpioPinId PIN_GREEN = 12;
    const GpioPinId PIN_BLUE = 13;

    const std::array<GpioPinId, 3> RGB_STRIP_PINS = { PIN_RED, PIN_GREEN, PIN_BLUE };


    /// Inversed signaling
    uint8_t make_led_value(uint32_t input)
    {
        if (input >= 255)
        {
            return 0;
        }

        auto unit_value = static_cast<float>(input) / 255;
        // x = x^4
        unit_value = unit_value * unit_value * unit_value * unit_value;
        
        auto output = std::min(
            static_cast<uint8_t>(unit_value * 255),
            static_cast<uint8_t>(255)
        );

        return 255 - output;
    }

    mgos_pwm_rgb_led rgb_strip = {};
    mg_connection* current_connection = nullptr;

    extern "C" void on_network_event(mg_connection*, int event, void* event_data, void*)
    {
        switch(event)
        {
            case MG_EV_WEBSOCKET_FRAME:
            {
                const auto* message = reinterpret_cast<const websocket_message*>(event_data);

                if ((message->flags & 0x0F) != WEBSOCKET_OP_TEXT || message->size == 0)
                {
                    return;
                }

                std::istringstream stream(std::string(
                    reinterpret_cast<const char*>(message->data), 
                    reinterpret_cast<const char*>(message->data + message->size)
                ));
                
                uint32_t r = 0, g = 0, b = 0, w = 0;
                stream >> r >> g >> b >> w;

                mgos_pwm_rgb_led_set(
                    &rgb_strip,
                    make_led_value(r),
                    make_led_value(g),
                    make_led_value(b),
                    make_led_value(w)
                );

                return;
            }
        }
    }

    extern "C" void on_network_connection_event(int event, void* event_data, void*)
    {
        mgos_net_event_data* net_event_data = reinterpret_cast<mgos_net_event_data*>(event_data);

        switch(event)
        {
            case MGOS_NET_EV_DISCONNECTED:
            {
                std::cout << "[!] Network disconnected" << std::endl;

                current_connection = nullptr;

                return;
            }
            
            case MGOS_NET_EV_IP_ACQUIRED:
            {
                const size_t MAX_IP_ADDR_STR_SIZE = 16;

                char ip_str[MAX_IP_ADDR_STR_SIZE] = {};
                mgos_net_ip_to_str(&net_event_data->ip_info.ip, ip_str);

                std::cout << "[!] Network connected! IP: " << ip_str << std::endl;

                current_connection =  mg_bind(mgos_get_mgr(), ":8266", on_network_event, nullptr);
                mg_set_protocol_http_websocket(current_connection);

                return;
            }
        }
    }
}

extern "C" mgos_app_init_result mgos_app_init() 
{
    for (auto pin : RGB_STRIP_PINS)
    { 
        mgos_gpio_setup_output(pin, PIN_VALUE_COLOR_DISABLE);
        mgos_gpio_set_mode(pin, MGOS_GPIO_MODE_OUTPUT);
    }
    
    mgos_pwm_rgb_led_init(
        &rgb_strip,
        PIN_RED,
        PIN_GREEN,
        PIN_BLUE
    );

    mgos_pwm_rgb_led_set(
        &rgb_strip,
        make_led_value(0),
        make_led_value(0),
        make_led_value(0),
        make_led_value(0)
    );

    mgos_event_add_group_handler(MGOS_EVENT_GRP_NET, on_network_connection_event, nullptr);

    return MGOS_APP_INIT_SUCCESS;
}
