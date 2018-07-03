#include <stdlib.h>
#include "OSAL.h"
#include "OSAL_Timer.h"
#include "OSAL_Task.h"
#include "Window.h"

#include "Task_Hr.h"
#include "Task_Upload.h"
#include "Task_Motor.h" 
#include "Task_Store.h"
#include "UserSetting.h"
#include "Task_Flash.h"
#include "Task_Battery.h"
#include "HeartComp.h"

#include "Board.h"
#include "nrf_saadc.h"
#include "nrf_gpio.h"
#include "Debug.h"
#include "nrf_delay.h"

#include "em70x8.h"

void hr_pwr_enable( bool enable);

void hr_timer_disable(void)
{
	hr_clock_rtc_stop();
	hr_pwr_enable(false);
	nrf_saadc_disable();
	
	sleepEnable = 1;	
}

nrf_saadc_value_t  saadc_buff1[4];

/* 
	RESULT = [V(P) - V(N) ] * GAIN/REFERENCE * 2(RESOLUTION - m)
	V(P)
		is the voltage at input P
	V(N)
		is the voltage at input N
	GAIN
		is the selected gain setting
	REFERENCE
		is the selected reference voltage

	and m=0 if CONFIG.MODE=SE, or m=1 if CONFIG.MODE=Diff

	2^14 = 16383
*/

unsigned long taskHrTaskId;
short current_hr_adc, current_touch_adc;
int to_close;

bool leaveEnable = false;
volatile unsigned long dect_mTicks = 0, need_mTicks = 0;
volatile unsigned char last_hr = 0, hr_showFlag = 0;
extern bool font_is_ok(void);

void hr_callback(void)
{		
}

unsigned int leave_time,leaveFlag = 0;
unsigned char hr_reset_flag = 0;
unsigned char upload_flag = 0;

unsigned long taskHr( unsigned long task_id, unsigned long events )
{ 	
	if ( events & TASK_HR_SENSOR_OK_EVT )
	{		
		hr_pwr_enable(false);
        nrf_gpio_cfg_output(HRS_SCL_PIN);
        nrf_gpio_cfg_output(HRS_SDA_PIN);
        nrf_gpio_pin_clear(HRS_SCL_PIN); 	
        nrf_gpio_pin_clear(HRS_SDA_PIN); 	
        
        osal_start_timerEx ( task_id, TASK_HR_PW_ENABLE_EVT, 250 );
		
		return ( events ^ TASK_HR_SENSOR_OK_EVT );
	}	
		
	if ( events & TASK_HR_PW_ENABLE_EVT )
	{
        nrf_gpio_pin_pull_t config_1 = NRF_GPIO_PIN_PULLDOWN;
        nrf_gpio_pin_pull_t config_2 = NRF_GPIO_PIN_PULLDOWN;        
        
        hr_pwr_enable(true);
        nrf_delay_ms(5);
        EM7028_hrs_init();
        
        if ( pid == 0x36 )
        {
            // 传感器在线：开始进行测量
            hr.ok = 1;
            osal_start_timerEx ( task_id, TASK_HR_SENSOR_OK_EVT, 1000 );
        }else{
            // 传感器离线：按照引脚的方式进行检测
 
            nrf_gpio_cfg_input(HRS_SDA_PIN, config_1);
            nrf_gpio_cfg_input(HRS_SCL_PIN, config_2);	
            
            int tmp = 0;

            if ( (nrf_gpio_pin_read(HRS_SDA_PIN) == 1) &&
			(nrf_gpio_pin_read(HRS_SCL_PIN) == 1) )
            {
                tmp++;
            }
            
            hr_pwr_enable(false);
            
            if ( (nrf_gpio_pin_read(HRS_SDA_PIN) == 0) &&
			(nrf_gpio_pin_read(HRS_SCL_PIN) == 0) )
            {
                tmp++;
            }            
            
            if ( tmp == 2 )
            {
                hr.hr = 1;
            }
            
            osal_start_timerEx ( task_id, TASK_HR_SENSOR_OK_EVT, 100 );
        }
        
		return ( events ^ TASK_HR_PW_ENABLE_EVT );
	}
		
	return 0;
}

void hr_pwr_enable( bool enable)
{
	if ( enable == true)
	{ 
		nrf_gpio_pin_clear(HR_PWR_PIN); 			
	}else{ 
		nrf_gpio_pin_set(HR_PWR_PIN); 			
	}
}

void taskHrInit( unsigned long task_id )
{
	taskHrTaskId = task_id;
	
    nrf_gpio_cfg_output(HR_PWR_PIN);
	nrf_gpio_pin_set(HR_PWR_PIN);	
	
	hr_clock_rtc_init();	
	
	hr.ok = 0;
	osal_start_timerEx( task_id, TASK_HR_PW_ENABLE_EVT, 250);
}
