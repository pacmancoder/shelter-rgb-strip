#include "private/module_initializers.hpp"

#include <tcpip_adapter.h>
#include <nvs_flash.h>

using namespace Unicorn;

void Hal::InitializeTcpIpStack()
{
    tcpip_adapter_init();
}

void Hal::InitializeNvsFlash()
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
}
