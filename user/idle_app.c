// =============================================================================
//  FileName    :	idle_app.c
//  Author      :	author
//  Email       :	email@email.com
//  Description :	使用空闲任务
//  Version     :	1.0
//  LastChange  :	2023-01-24 09:26:04
//  ChangeLog   :
// =============================================================================
#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

unsigned char pcWriteBuffer[512];
/**
 * @brief 在任意时刻，总要有一个task在运行，因此不能在空闲任务里使用任何可以使任务阻塞的函数
 */
void vApplicationIdleHook(void)
{
    printf("任务名\t任务状态\t优先级\t剩余栈\t任务序号\n");
    vTaskList((char*)&pcWriteBuffer);
    printf("%s\n", pcWriteBuffer);

    printf("\n任务名\t运行计数\t使用率\n");
    vTaskGetRunTimeStats((char*)&pcWriteBuffer);
    printf("%s\n", pcWriteBuffer);
    // vTaskDelay(100);  // 程序会崩溃
}
/*-----------------------------------------------------------*/

int main(void)
{
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
