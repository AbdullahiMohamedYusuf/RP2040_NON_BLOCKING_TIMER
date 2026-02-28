#include "pico/stdlib.h"
#include "hardware/timer.h"

#define PIN_14 14
#define PIN_15 15
#define PIN_13 13

/*
timer_busy_wait_until
void timer_busy_wait_until (timer_hw_t * timer, absolute_time_t t)

Busy wait wasting cycles until after the specified timestamp using the given timer instance.

Parameters:
timer: the timer instance
t: Absolute time to wait until

*/

int delay_ms(uint32_t ms)
{
    uint32_t start_time = timer_hw->timelr;
    uint32_t delay_ticks = ms * 1000;
    while ((timer_hw->timelr - start_time) < delay_ticks)
    {
        tight_loop_contents();
    }
    start_time = timer_hw->timelr;
    return 1;
}


int main()
{
    stdio_init_all();
    int toggle = 0;
    // Initialize pin 14
    gpio_init_mask((1 << PIN_14) | (1 << PIN_15) | (1 << PIN_13));
    gpio_set_dir_all_bits((1 << PIN_14) | (1 << PIN_15) | (1 << PIN_13));

    uint64_t event_trigger_time = timer_hw->timelr + 1000000; // 1 second in microseconds

    // Keep program running
    while (true)
    {
        if (timer_hw->timelr >= event_trigger_time)
        {
            toggle = !toggle; // Toggle the state
            event_trigger_time = timer_hw->timelr + 1000000; // Reset the trigger time for next toggle
        }
        
        if (toggle)
        {
            gpio_put(PIN_14, 1);
            gpio_put(PIN_15, 0);
            gpio_put(PIN_13, 0);
        }
        else
        {
            gpio_put(PIN_14, 0);
            gpio_put(PIN_15, 1);
            gpio_put(PIN_13, 1);
        }
    }
}