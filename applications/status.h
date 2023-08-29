#ifndef __STATUS_H
#define __STATUS_H

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>



typedef struct {
    rt_uint8_t orangepi;
    rt_uint32_t time_limit;
    rt_uint32_t time_count;
    
    rt_uint8_t is_set_time;
} status_t;



extern status_t status;
//key include status





#endif
