#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "projdefs.h"
#include "task.h"
#include "timers.h"
#include "event_groups.h"

void vApplicationIdleHook(void)
{
}

static EventGroupHandle_t xCreateEventGroup = NULL;

void Task1(void *pvParameter)
{
    EventBits_t uxBits;
    while(1)
    {
        uxBits = xEventGroupWaitBits(xCreateEventGroup, 0x03, pdTRUE, pdTRUE, 1000 / portTICK_RATE_MS);
        if((uxBits & 0x03) == 0x03)
        {
            printf("xEventGroupWaitBits success! uxBits = %d\n", uxBits);
        }
        else
        {
            printf("xEventGroupWaitBits failed! uxBits = %d\n", uxBits);
        }
    }
}

void Task2(void *pvParameter)
{
    EventBits_t   uxBits;
    unsigned char flag = 0;
    while(1)
    {
        printf("-------------------Set uxBits = %d\n", flag);
        uxBits = xEventGroupSetBits(xCreateEventGroup, flag);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        if(flag == 0x03)
            flag = 0;
        else
            flag++;
    }
}

int main(void)
{
    xCreateEventGroup = xEventGroupCreate();
    if(xCreateEventGroup == NULL)
        printf("xEventGroupCreate failed!\n");

    xTaskCreate(Task1, "Task1", 1024, NULL, 2, NULL);
    xTaskCreate(Task2, "Task2", 1024, NULL, 2, NULL);

    vTaskStartScheduler();
    return 0;
}

void vAssertCalled(unsigned long ulLine, const char *const pcFileName)
{
    taskENTER_CRITICAL();
    {
        printf("[ASSERT] %s:%lu\n", pcFileName, ulLine);
        fflush(stdout);
    }
    taskEXIT_CRITICAL();
    exit(-1);
}
