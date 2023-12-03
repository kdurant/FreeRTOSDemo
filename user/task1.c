#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
//#include "queue.h"
void vTask1(void*);
void vTask2(void*);
void vTask3(void*);
void vTask4(void*);

void vApplicationIdleHook(void);

int main(void)
{
    printf("Total Heap size: %d\n", xPortGetFreeHeapSize());
    /* Creating Two Task Same Priorities and Delay*/
    xTaskCreate(vTask1, "Task 1", 1000, NULL, 2, NULL);
    printf("Afte create task1 Heap size: %d\n", xPortGetFreeHeapSize());
    xTaskCreate(vTask2, "Task 2", 1000, NULL, 2, NULL);
    printf("Afte create task2 Heap size: %d\n", xPortGetFreeHeapSize());
    /* Creating Two Task Same Priorities and DelayUntil*/
    xTaskCreate(vTask3, "Task 3", 1000, NULL, 1, NULL);
    printf("Afte create task3 Heap size: %d\n", xPortGetFreeHeapSize());
    xTaskCreate(vTask4, "Task 4", 1000, NULL, 1, NULL);
    printf("Afte create task4 Heap size: %d\n", xPortGetFreeHeapSize());

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

void vTask1(void* parameter)
{
    while(1)
    {
        // taskYIELD();
    }
}
void vTask2(void* parameter)
{
    while(1)
    {
        printf("Task 2\n");
        vTaskDelay(pdMS_TO_TICKS(250));
    }
}
void vTask3(void* parameter)
{
    TickType_t xLastWaketime = xTaskGetTickCount();
    while(1)
    {
        printf("Task 3 with 250ms\n");
        vTaskDelayUntil(&xLastWaketime, pdMS_TO_TICKS(250));
    }
}
void vTask4(void* parameter)
{
    TickType_t xLastWaketime = xTaskGetTickCount();
    while(1)
    {
        printf("Task 4 with 500ms\n");
        vTaskDelayUntil(&xLastWaketime, pdMS_TO_TICKS(500));
    }
}

/* CH3_TASKMANAGEMENT ends */

void vApplicationIdleHook(void)
{
    //	printf("Idle\r\n");
}
/*-----------------------------------------------------------*/
