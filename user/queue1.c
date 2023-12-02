#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "portmacro.h"
#include "projdefs.h"
#include "task.h"
#include "timers.h"
#include "queue.h"

static TaskHandle_t  xHandleTask1 = NULL;
static TaskHandle_t  xHandleTask2 = NULL;
static QueueHandle_t xQueue       = NULL;

void vApplicationIdleHook(void)
{
    // printf("Idle\r\n");
}

void Task1(void* pvParameters)
{
    TickType_t xLastWaketime = xTaskGetTickCount();
    int        value         = 0;
    while(1)
    {
        vTaskDelayUntil(&xLastWaketime, 1000 / portTICK_PERIOD_MS);
        xQueueSend(xQueue, (void*)&value, 1000 / portTICK_PERIOD_MS);
        value++;

        printf("uxQueueSpacesAvailable() = %d\n", uxQueueSpacesAvailable(xQueue));
    }
}
void Task2(void* pvParameters)
{
    BaseType_t       xResult;
    const TickType_t xMaxBlockTime = pdMS_TO_TICKS(2000);
    int              value;
    while(1)
    {
        xResult = xQueueReceive(xQueue, (void*)&value, xMaxBlockTime);
        if(xResult == pdPASS)
            printf("Received value = %d\n", value);
        else
        {
            printf("Received failed\n");
        }
        // 阻塞此任务，可以看到queue剩余空间逐渐变小
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

int main(void)
{
    // 一般情况下队列不应该属于某个具体的任务
    xQueue = xQueueCreate(128, sizeof(int));

    xTaskCreate(Task1, "Task1", 1024, NULL, 4, xHandleTask1);
    xTaskCreate(Task2, "Task2", 1024, NULL, 1, xHandleTask2);
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
