#include "key.h"
#include "button.h"

#include "status.h"
#include "beep.h"

rt_uint8_t key = 0;
Button_t btn_green, btn_yelow1, btn_yelow2, btn_red;

/*--------------------------------- 按键处理函数 --------------------------- */
uint8_t read_btn_green(void)
{
    return rt_pin_read(KEY_GREEN_PIN);
}

void btn_green_down_cb(void *btn)
{
    status.is_set_time = 1;
    key = 1;
    rt_kprintf("Button green once press\n");
}

void btn_green_double_cb(void *btn)
{
    status.is_set_time = 0;
    
    //rt_pin_write(BEEP_PIN, PIN_HIGH);
    
    key = 5;
    rt_kprintf("Button green double press\n");
}

//////////////////////////////////

uint8_t read_btn_yelow1(void)
{
    return rt_pin_read(KEY_YELLOW1_PIN);
}

void btn_yelow1_down_cb(void *btn)
{
    status.time_count = 0;
    status.time_limit += 10;
    key = 2;
    rt_kprintf("Button yelow1 once press\n");
}

void btn_yelow1_double_cb(void *btn)
{
    key = 6;
    rt_kprintf("Button yelow1 double press\n");
}


//////////////////////////////////

uint8_t read_btn_yelow2(void)
{
    return rt_pin_read(KEY_YELLOW2_PIN);
}

void btn_yelow2_down_cb(void *btn)
{
    status.time_count = 0;
    status.time_limit -= 10;
    key = 3;
    rt_kprintf("Button yelow2 once press\n");
}

void btn_yelow2_double_cb(void *btn)
{
    key = 7;
    rt_kprintf("Button yelow2 double press\n");
}

//////////////////////////////////

uint8_t read_btn_red(void)
{
    return rt_pin_read(KEY_RED_PIN);
}

void btn_red_down_cb(void *btn)
{
    key = 4;
    rt_kprintf("Button red once press\n");
}

void btn_red_double_cb(void *btn)
{
    key = 8;
    rt_kprintf("Button red double press\n");
}

/*--------------------------  数据处理线程  ---------------------------*/

static void key_thread_entry(void *parameter)
{
    rt_pin_mode(KEY_OUTPUT_PIN, PIN_MODE_OUTPUT_OD);
    
    rt_pin_mode(KEY_GREEN_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(KEY_YELLOW1_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(KEY_YELLOW2_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(KEY_RED_PIN, PIN_MODE_INPUT_PULLUP);
    
    rt_pin_write(KEY_OUTPUT_PIN, PIN_LOW);
    
    
    Button_Create("btn_green", &btn_green, read_btn_green, PIN_LOW);
    Button_Attach(&btn_green, BUTTON_DOWM, btn_green_down_cb);
    Button_Attach(&btn_green, BUTTON_DOUBLE, btn_green_double_cb);
    Get_Button_Event(&btn_green);

    Button_Create("btn_yelow1", &btn_yelow1, read_btn_yelow1, PIN_LOW);
    Button_Attach(&btn_yelow1, BUTTON_DOWM, btn_yelow1_down_cb);
    Button_Attach(&btn_yelow1, BUTTON_DOUBLE, btn_yelow1_double_cb);
    Get_Button_Event(&btn_yelow1);
    
    Button_Create("btn_yelow2", &btn_yelow2, read_btn_yelow2, PIN_LOW);
    Button_Attach(&btn_yelow2, BUTTON_DOWM, btn_yelow2_down_cb);
    Button_Attach(&btn_yelow2, BUTTON_DOUBLE, btn_yelow2_double_cb);
    Get_Button_Event(&btn_yelow2);

    Button_Create("btn_red", &btn_red, read_btn_red, PIN_LOW);
    Button_Attach(&btn_red, BUTTON_DOWM, btn_red_down_cb);
    Button_Attach(&btn_red, BUTTON_DOUBLE, btn_red_double_cb);
    Get_Button_Event(&btn_red);

    while (1)
    {
//        key.green = rt_pin_read(KEY_GREEN_PIN);
//        key.yellow1 = rt_pin_read(KEY_YELLOW1_PIN);
//        key.yellow2 = rt_pin_read(KEY_YELLOW2_PIN);
//        key.red = rt_pin_read(KEY_RED_PIN);
        
        Button_Process();
        
        rt_thread_mdelay(10);
    }
}

int key_init(void)
{
    rt_err_t ret = RT_EOK;

    /* 创建 serial 线程 */
    rt_thread_t thread = rt_thread_create("key", 
                                        key_thread_entry, 
                                        RT_NULL, 
                                        KEY_THREAD_STACK_SIZE, 
                                        KEY_THREAD_PRIORITY, 
										KEY_THREAD_TIMESLICE);
    
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
INIT_APP_EXPORT(key_init);





