#include <assert.h>
#include <stdint.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <driver/gpio.h>

/* Assertions which check that current FFI interface is valid */
_Static_assert(sizeof(int) == sizeof(int32_t), "Incompatible FFI");
_Static_assert(sizeof(TickType_t) == sizeof(uint32_t), "Incompatible FFI");
_Static_assert(sizeof(gpio_num_t) == sizeof(uint32_t), "Incompatible FFI");
_Static_assert(sizeof(esp_err_t) == sizeof(int32_t), "Incompatible FFI");


/* Entry point implementation defined in the rust code */
extern void unicorn_main(void);

/* Entry point proxy for ESP-IDF */
void app_main(void) {
    unicorn_main();
}

/* Shim functions */

uint32_t idf_shim_get_port_tick_rate() {
    return portTICK_RATE_MS;
}

int32_t idf_shim_configure_gpio(
    uint32_t pinMask,
    uint32_t mode,
    uint32_t enablePullUp,
    uint32_t enablePullDown,
    uint32_t interruptType
) {
    gpio_config_t ioConf;
    ioConf.pin_bit_mask = pinMask;
    ioConf.mode = mode;
    ioConf.pull_up_en = enablePullUp;
    ioConf.pull_down_en = enablePullDown;
    ioConf.intr_type = interruptType;
    return gpio_config(&ioConf);
}
