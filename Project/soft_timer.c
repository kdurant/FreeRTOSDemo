#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

void vApplicationIdleHook(void)
{
}

static TimerHandle_t xTimer = NULL;

unsigned char pcWriteBuffer[512];
void          vTimerCallback(void)
{
    printf("Timer callback\n");
    printf("tick = %d\n", xTaskGetTickCount());

    printf("---------------vTaskList-----------\n");
    vTaskList((char*)&pcWriteBuffer);
    printf("%s", pcWriteBuffer);
    // vTaskDelay(100);  // 程序会崩溃
}

int main(void)
{
    xTimer = xTimerCreate("Timer", 1000 / portTICK_PERIOD_MS, pdTRUE, NULL, vTimerCallback);
    if(xTimer != NULL)
    {
        xTimerStart(xTimer, 1000 / portTICK_PERIOD_MS);
    }
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
