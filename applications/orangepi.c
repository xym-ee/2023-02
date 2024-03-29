#include "orangepi.h"

#include "status.h"




/*-----------------------------------------  香橙派数据接收 ----------------------------------------*/

rt_int8_t counter = 'w'; //wait


#define SAMPLE_UART_NAME       "uart3"


static struct rt_semaphore rx_sem;
static rt_device_t serial;


static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
    rt_sem_release(&rx_sem);

    return RT_EOK;
}

static void serial_thread_entry(void *parameter)
{
    char ch;

    while (1)
    {
        while (rt_device_read(serial, -1, &ch, 1) != 1)
        {  
            rt_sem_take(&rx_sem, RT_WAITING_FOREVER);
        }
        
        counter = ch;
    }
}

int uart_sample(void)
{
    rt_err_t ret = RT_EOK;

    serial = rt_device_find(SAMPLE_UART_NAME);
    if (!serial)
    {
        rt_kprintf("find %s failed!\n", SAMPLE_UART_NAME);
        return RT_ERROR;
    }

    rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
    rt_device_open(serial, RT_DEVICE_FLAG_INT_RX);
    rt_device_set_rx_indicate(serial, uart_input);

    rt_thread_t thread = rt_thread_create("serial", serial_thread_entry, RT_NULL, 1024, 25, 10);

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

INIT_APP_EXPORT(uart_sample);


