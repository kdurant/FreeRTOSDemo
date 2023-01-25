#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

void vApplicationIdleHook(void)
{
}

void Task1(void* pvParameter)
{
    while(1)
    {
        printf("tick = %d\n", xTaskGetTickCount());
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        printf("tick = %d\n", xTaskGetTickCount());
    }
}

int main(void)
{
    xTaskCreate(Task1, "Task 1", 1024, NULL, 1, NULL);
    vTaskStartScheduler();
    return 0;
}

void vAssertCalled(unsigned long ulLine, const char* const pcFileName)
{
    taskENTER_CRITICAL();
    {
        printf("[ASSERT] %s:%lu\n", pcFileName, ulLine);
        fflush(stdout);
    }
    taskEXIT_CRITICAL();
    exit(-1);
}
