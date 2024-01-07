#include <stdbool.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

#define TASK1_PERIOD_MS  20
#define TASK2_PERIOD_MS  39

#define MULTIPLIER1 2
#define MULTIPLIER2 3

static const char TAG[] = "010";

typedef struct {
    uint32_t i;
    uint32_t j;
    uint32_t k;
} sharedStruct_t;

volatile sharedStruct_t sharedStruct = {0, 0, 0};

void vTaskCode1(void *pvParameters) {

    while (true) {
        sharedStruct.i = 100;
        vTaskDelay(pdMS_TO_TICKS(TASK1_PERIOD_MS));
        sharedStruct.j = 100;
        vTaskDelay(pdMS_TO_TICKS(TASK1_PERIOD_MS));
        sharedStruct.k = sharedStruct.i - sharedStruct.j;
        vTaskDelay(pdMS_TO_TICKS(TASK1_PERIOD_MS));
        sharedStruct.i = 0;
        vTaskDelay(pdMS_TO_TICKS(TASK1_PERIOD_MS));
        sharedStruct.j = 0;
        ESP_LOGI(TAG, "1 - %lu %lu %lu",
                 sharedStruct.i,
                 sharedStruct.j,
                 sharedStruct.k);
    }

}

void vTaskCode2(void *pvParameters) {

    while (true) {
        sharedStruct.j = 200;
        vTaskDelay(pdMS_TO_TICKS(TASK2_PERIOD_MS));
        sharedStruct.k = 200;
        vTaskDelay(pdMS_TO_TICKS(TASK2_PERIOD_MS));
        sharedStruct.i = sharedStruct.i - sharedStruct.j;
        vTaskDelay(pdMS_TO_TICKS(TASK2_PERIOD_MS));
        sharedStruct.j = 0;
        vTaskDelay(pdMS_TO_TICKS(TASK2_PERIOD_MS));
        sharedStruct.k = 0;
        ESP_LOGI(TAG, "2 - %lu %lu %lu",
                 sharedStruct.i,
                 sharedStruct.j,
                 sharedStruct.k);
    }

}

void app_main(void) {

    BaseType_t os_rs = xTaskCreatePinnedToCore(
            vTaskCode1,         // Task code.
            "OurFirstTask",     // Task name.
            2048,               // Task stack depth (in bytes).
            NULL,               // Task parameters. Not used here.
            5,                  // Priority.
            NULL,               // Task handle (output). Not used here.
            APP_CPU_NUM         // Run task on APP_CPU.
            );
    if (os_rs != pdPASS) {
        ESP_LOGE(TAG, "Error from xTaskCreatePinnedToCore: %d", os_rs);
        goto exit_on_fatal_error;
    }
    // The app_main function may return.

    os_rs = xTaskCreatePinnedToCore(
                vTaskCode2,         // Task code.
                "OurSecondTask",    // Task name.
                2048,               // Task stack depth (in bytes).
                NULL,               // Task parameters. Not used here.
                5,                  // Priority.
                NULL,               // Task handle (output). Not used here.
                APP_CPU_NUM         // Run task on APP_CPU.
                );
    if (os_rs != pdPASS) {
        ESP_LOGE(TAG, "Error from xTaskCreatePinnedToCore: %d", os_rs);
        goto exit_on_fatal_error;
    }

    exit_on_fatal_error:
    ESP_LOGI(TAG, "Exiting");

}
