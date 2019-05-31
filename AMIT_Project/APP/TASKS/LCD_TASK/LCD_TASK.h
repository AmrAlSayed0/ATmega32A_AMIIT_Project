#ifndef AMIT_PROJECT_LCD_TASK_H_
#define AMIT_PROJECT_LCD_TASK_H_
#include "common.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
extern QueueHandle_t xLCD_Queue;
void vLCD_TASK ( void* vParameters );
#endif
