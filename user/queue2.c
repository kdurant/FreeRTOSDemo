#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "portmacro.h"
#include "projdefs.h"
#include "task.h"
#include "timers.h"
#include "queue.h"

typedef struct __frame
{
    uint8_t data[256];
    uint8_t len;
} frame_t;

static TaskHandle_t  xHandleTask1 = NULL;
static TaskHandle_t  xHandleTask2 = NULL;
static QueueHandle_t xQueue       = NULL;

void vApplicationIdleHook(void)
{
    // printf("Idle\r\n");
}

void SendTask(void* pvParameters)
{
    TickType_t xLastWaketime = xTaskGetTickCount();
    frame_t    frame;
    frame.len = 10;
    int idx   = 1;
    for(int i = 0; i < frame.len; i++)
        frame.data[i] = i * idx;
    while(1)
    {
        vTaskDelayUntil(&xLastWaketime, 1000 / portTICK_PERIOD_MS);
        xQueueSend(xQueue, (void*)&frame, 1000 / portTICK_PERIOD_MS);
        printf("SendTask: write\n");
        idx++;
        for(int i = 0; i < frame.len; i++)
            frame.data[i] = i * idx;

        printf("uxQueueSpacesAvailable() = %d\n", uxQueueSpacesAvailable(xQueue));
    }
}
void RecvTask(void* pvParameters)
{
    BaseType_t       xResult;
    const TickType_t xMaxBlockTime = pdMS_TO_TICKS(2000);
    frame_t          frame;
    while(1)
    {
        xResult = xQueueReceive(xQueue, (void*)&frame, xMaxBlockTime);
        if(xResult == pdPASS)
        {
            printf("Received data length = %d\n", frame.len);
            for(int i = 0; i < frame.len; i++)
            {
                printf("%d\t", frame.data[i]);
            }
            printf("\n");
        }
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
    xQueue = xQueueCreate(128, sizeof(frame_t));

    xTaskCreate(SendTask, "SendTask", 1024, NULL, 4, xHandleTask1);
    xTaskCreate(RecvTask, "RecvTask", 1024, NULL, 1, xHandleTask2);
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
