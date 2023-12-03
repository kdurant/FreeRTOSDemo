#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
//#include "queue.h"
void vTask1(void*);
void vTask2(void*);

void vApplicationIdleHook(void);

void vApplicationStackOverflowHook(TaskHandle_t xTask, signed char* pcTaskName);

int main(void)
{
    /* Creating Two Task Same Priorities and Delay*/
    xTaskCreate(vTask1, "Task 1", 256, NULL, 2, NULL);
    xTaskCreate(vTask2, "Task 2", 1000, NULL, 2, NULL);

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
    int buf[2048] = {1};
    while(1)
    {
        printf("Task 1\n");
        for(int i = 0; i < 2048; i++)
            printf("%d ", buf[i]);
        printf("%d\n");
        vTaskDelay(pdMS_TO_TICKS(250));
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

/* CH3_TASKMANAGEMENT ends */

void vApplicationIdleHook(void)
{
    //	printf("Idle\r\n");
}


void vApplicationStackOverflowHook(TaskHandle_t xTask, signed char* pcTaskName)
{
    printf("任务： %s 发现栈溢出\r\n", pcTaskName);
}
