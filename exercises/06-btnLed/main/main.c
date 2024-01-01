#include <stdbool.h>
#include <unistd.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "btn_task.h"
#include "common.h"
#include "led_task.h"

#define SLEEP_PERIOD_MS 50

void app_main(void)
{

	// Initialize communication flags.
	push_event = false;

	btn_task_init();
	led_task_init();

	while (true) {

		// If we don't sleep a little, ESP-IDF considers there is a problem:
		// a watchdog resets the microcontroller.
		vTaskDelay(pdMS_TO_TICKS(SLEEP_PERIOD_MS));

		btn_task_run();
		led_task_run();

	}

}
