// =============================================================================
//  FileName    :	task_priority.c
//  Author      :	author
//  Email       :	email@email.com
//  Description :	创建两个任务，高优先级的任务始终运行，低优先级的任务无法运行
//  Version     :	1.0
//  LastChange  :	2023-01-24 09:26:47
//  ChangeLog   :
// =============================================================================
#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

static TaskHandle_t xHandleTask1 = NULL;
static TaskHandle_t xHandleTask2 = NULL;

void vApplicationIdleHook(void)
{
    // printf("Idle\r\n");
}

void Task1(void* pvParameters)
{
    while(1)
    {
        printf("Task1 %d\n", uxTaskPriorityGet(xHandleTask1));
    }
}
void Task2(void* pvParameters)
{
    while(1)
    {
        printf("Task2\n");
    }
}

int main(void)
{
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
