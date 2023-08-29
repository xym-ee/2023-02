#include "beep.h"
#include "status.h"
#include "key.h"
/*--------------------------  数据处理线程  ---------------------------*/

static void beep_thread_entry(void *parameter)
{
    rt_pin_mode(BEEP_PIN, PIN_MODE_OUTPUT);
    
    rt_pin_write(BEEP_PIN, PIN_LOW);
    
    while (1)
    {
        if (status.time_count > status.time_limit)
        {
            rt_pin_write(BEEP_PIN, PIN_HIGH);
            rt_thread_mdelay(600);
            rt_pin_write(BEEP_PIN, PIN_LOW);
            rt_thread_mdelay(400);
        
            rt_pin_write(BEEP_PIN, PIN_HIGH);
            rt_thread_mdelay(600);
            rt_pin_write(BEEP_PIN, PIN_LOW);
            rt_thread_mdelay(400);

            rt_pin_write(BEEP_PIN, PIN_HIGH);
            rt_thread_mdelay(600);
            rt_pin_write(BEEP_PIN, PIN_LOW);
            rt_thread_mdelay(1000);

            rt_pin_write(BEEP_PIN, PIN_HIGH);
            rt_thread_mdelay(600);
            rt_pin_write(BEEP_PIN, PIN_LOW);
            rt_thread_mdelay(400);
        
            rt_pin_write(BEEP_PIN, PIN_HIGH);
            rt_thread_mdelay(600);
            rt_pin_write(BEEP_PIN, PIN_LOW);
            rt_thread_mdelay(400);

            rt_pin_write(BEEP_PIN, PIN_HIGH);
            rt_thread_mdelay(600);
            rt_pin_write(BEEP_PIN, PIN_LOW);
            rt_thread_mdelay(1000);

            status.time_limit = RT_UINT32_MAX;
        }
        
        if (key == 5)
        {
            key = 0;
            rt_pin_write(BEEP_PIN, PIN_HIGH);
            rt_thread_mdelay(1000);
            rt_pin_write(BEEP_PIN, PIN_LOW);
        }        
                
        rt_thread_mdelay(1000);
    }
}

int beep_init(void)
{
    rt_err_t ret = RT_EOK;

    /* 创建 serial 线程 */
    rt_thread_t thread = rt_thread_create("beep", 
                                        beep_thread_entry, 
                                        RT_NULL, 
                                        BEEP_THREAD_STACK_SIZE, 
                                        BEEP_THREAD_PRIORITY, 
										BEEP_THREAD_TIMESLICE);
    
    /* 创建成功则启动线程 */
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        ret = RT_ERROR;
    }

    return ret;
}

/* 导出命令 or 自动初始化 */
INIT_APP_EXPORT(beep_init);





