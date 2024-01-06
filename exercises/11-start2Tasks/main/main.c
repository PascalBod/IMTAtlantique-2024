#include <stdbool.h>
#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

#define MAIN_LOOP_PERIOD_MS 5000

static const char TAG[] = "011";

typedef struct {
    uint32_t task_id;
    uint32_t task_period;
} params_t;

static params_t params1;
static params_t params2;

void vTaskCode(void *pvParameters) {

    params_t *paramsPtr = (params_t *)pvParameters;

    while (true) {
        ESP_LOGI(TAG, "Hello from task %lu!", paramsPtr->task_id);
        vTaskDelay(pdMS_TO_TICKS(paramsPtr->task_period));
    }

}

void app_main(void) {

    // TODO - Start two tasks, the first one with a period of 500 ms, the second one
    // with a period of 1 s.

}
