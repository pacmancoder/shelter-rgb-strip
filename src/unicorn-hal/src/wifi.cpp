#include <hal/wifi.hpp>

#include <functional>
#include <string>
#include <algorithm>

#include <cstdio>

#include <esp_wifi.h>

namespace
{
    std::string ToHex(long value)
    {
        char buffer[32] = {};
        snprintf(buffer, sizeof(buffer), "%08lX", value);

        return buffer;
    }

    const std::string GetUniqueSsid()
    {
        static const auto hashedSeed = std::hash<std::string>()(__TIMESTAMP__);
        static const auto ssid = "[Shelter] Unicorn " + ToHex((long) hashedSeed);
        return ssid;
    }
}

Unicorn::Hal::Wifi::Wifi()
{
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
}

void Unicorn::Hal::Wifi::StartOpenAp()
{
    const auto& ssid = GetUniqueSsid();

    wifi_config_t config = {};
    std::copy(ssid.begin(), ssid.end(), config.ap.ssid);
    config.ap.ssid_len = ssid.size();
    config.ap.max_connection = 1;
    config.ap.authmode = WIFI_AUTH_OPEN;

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &config));
    ESP_ERROR_CHECK(esp_wifi_start());
}
