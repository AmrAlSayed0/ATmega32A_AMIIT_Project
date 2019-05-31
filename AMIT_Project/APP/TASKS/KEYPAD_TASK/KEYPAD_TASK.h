#ifndef AMIT_PROJECT_KEYPAD_TASK_H_
#define AMIT_PROJECT_KEYPAD_TASK_H_
#include "common.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
extern QueueHandle_t xKEYPAD_Queue;
void vKEYPAD_TASK ( void* vParameters );
#endif