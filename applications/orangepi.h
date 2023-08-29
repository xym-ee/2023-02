#ifndef __ORANGEPI_H
#define __ORANGEPI_H


#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>




extern rt_int8_t counter;


#define ORANGEPI_STATUS_PIN     GET_PIN(B, 0)

#define     ORANGEPI_THREAD_STACK_SIZE   256
#define     ORANGEPI_THREAD_PRIORITY     3
#define     ORANGEPI_THREAD_TIMESLICE    10

#endif

