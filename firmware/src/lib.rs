#![no_std]

extern crate panic_halt;

const LED_GPIO : u32 = 2;

extern "C" {
    fn gpio_set_level(gpio: u32, state: u32) -> i32;
    fn vTaskDelay(ticks: u32);

    fn idf_shim_get_port_tick_rate() -> u32;
    fn idf_shim_configure_gpio(
        pinMask: u32,
        mode: u32,
        enablePullUp: u32,
        enablePullDown: u32,
        interruptMode: u32
    ) -> i32;
}

fn setup_gpio() {
    unsafe {
        if idf_shim_configure_gpio(1u32 << LED_GPIO, 1u32 << 1, 0, 0, 0) != 0 {
            panic!("Can't configure gpio");
        }
    }
}

fn set_led_state(state: bool) {
    unsafe {
        if gpio_set_level(LED_GPIO, if state { 1 } else { 0 }) != 0 {
            panic!("Cant change gpio state");
        }
    }
}

fn sleep_ms(count: u32) {
    unsafe {
        vTaskDelay(count / idf_shim_get_port_tick_rate());
    }
}

#[no_mangle]
fn unicorn_main() {

    setup_gpio();

    let mut state = false;

    loop {
        set_led_state(state);
        state = !state;
        sleep_ms(1000);
    }
}
