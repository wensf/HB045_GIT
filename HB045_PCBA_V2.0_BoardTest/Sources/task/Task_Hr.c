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
#include "FFT.h"

void hr_pwr_enable( bool enable);

void hr_timer_disable(void)
{
	hr_clock_rtc_stop();
	hr_pwr_enable(false);
	HR_ADC_PIN_OUTPUT_LOW();
	nrf_saadc_disable();
	
	sleepEnable = 1;	
}

nrf_saadc_value_t  saadc_buff1[4];

static void hr_saadc_init(nrf_saadc_input_t pin, int channel)
{
	nrf_saadc_channel_config_t   nrf_saadc_channel_config;
	
	nrf_saadc_disable();
	
	/* Positive channel resistor c ontrol */
	nrf_saadc_channel_config.resistor_p = NRF_SAADC_RESISTOR_DISABLED;
	nrf_saadc_channel_config.resistor_n = NRF_SAADC_RESISTOR_DISABLED;
	/* Gain factor of the analog-to-digital converter input ??*/
	nrf_saadc_channel_config.gain       = NRF_SAADC_GAIN1_5; 
	/* Reference selection,Internal reference (0.6 V). ????*/
	nrf_saadc_channel_config.reference  = NRF_SAADC_REFERENCE_INTERNAL;
	/*Analog-to-digital converter acquisition time ???? */
	nrf_saadc_channel_config.acq_time   = NRF_SAADC_ACQTIME_20US;
	/*  Single ended, PSELN will be ignored, negative input to ADC shorted to GND. */
	nrf_saadc_channel_config.mode       = NRF_SAADC_MODE_SINGLE_ENDED;
	/* Input selection for the analog-to-digital converter.???? */
	nrf_saadc_channel_config.pin_p      = pin;
	nrf_saadc_channel_config.pin_n      = NRF_SAADC_INPUT_DISABLED;
	
	nrf_saadc_channel_init(channel, &nrf_saadc_channel_config);	
		
	/* 12 bits ADC */
	nrf_saadc_resolution_set(NRF_SAADC_RESOLUTION_12BIT);
							
	nrf_saadc_int_disable(NRF_SAADC_INT_END);
	
	/* Function for enabling the SAADC. */
	nrf_saadc_enable();
}

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

static nrf_saadc_value_t* saadc_buffer_convert(nrf_saadc_input_t pin, int channel)
{		
	/* initializing the SAADC result buffer */
	nrf_saadc_buffer_init(saadc_buff1, 1);
	
	// nrf_saadc_channel_input_set(channel, pin, NRF_SAADC_INPUT_DISABLED);	
	
	nrf_saadc_task_trigger(NRF_SAADC_TASK_START);
    nrf_saadc_task_trigger(NRF_SAADC_TASK_SAMPLE);
	
	uint32_t timeout = 1000000;
    while (0 == nrf_saadc_event_check(NRF_SAADC_EVENT_END) && timeout > 0)
    {
        timeout--;
    }
	nrf_saadc_event_clear(NRF_SAADC_EVENT_END);
	
	return saadc_buff1;
}

unsigned long taskHrTaskId;
short current_hr_adc, current_touch_adc;
int to_close;

bool leaveEnable = false;
volatile unsigned long dect_mTicks = 0, need_mTicks = 0;
volatile unsigned char last_hr = 0, hr_showFlag = 0;
extern bool font_is_ok(void);

void hr_callback(void)
{		
	hr_saadc_init(HR_TOUCH_LEVEL_ADC_PIN,0);
	saadc_buffer_convert(HR_TOUCH_LEVEL_ADC_PIN,0);	
	current_touch_adc = saadc_buff1[0];
	
	current_touch_adc = ( current_touch_adc < 0 )?0:current_touch_adc;
	current_touch_adc = ( current_touch_adc > 4095 )?(4095):(current_touch_adc);
	
	hr_saadc_init(HR_DET_ADC_PIN,0);
	saadc_buffer_convert(HR_DET_ADC_PIN,0);
	current_hr_adc = saadc_buff1[0];
	
	current_hr_adc = ( current_hr_adc < 0 )?0:current_hr_adc;
	current_hr_adc = ( current_hr_adc > 4095 )?(4095):(current_hr_adc);	
	
	osal_set_event( taskHrTaskId, TASK_HR_SAMPLE_EVT );
	
	if ( leaveEnable == true )  /* 正在数据采样中 */
	{
		fft_put(current_hr_adc, 0);
	}	
}
	
short leave_array[62]; // 2.5s (2500/25 = 62.5)

void leave_array_put( short val )
{
	for ( int i = 0; i < SIZEOF(leave_array)-1; i++ )
	{
		leave_array[i] = leave_array[i+1];
	}
	
	leave_array[SIZEOF(leave_array)-1] = val;
}

bool is_leave(void)
{
	int max = 0, min = 16384;
	
	for ( int i = 0; i < SIZEOF(leave_array); i++ )
	{
		if ( max < leave_array[i] )
		{
			max = leave_array[i];
		}
		
		if ( min > leave_array[i] )
		{
			min = leave_array[i];
		}
	}
	if ( abs(max-min) < 400 )   // 手腕脱离判断，最大最小波幅差值<400.
	{                           // 这是一个经验值，根据具体情况修改.
		return true;
	}else
	{
		return false;
	}
}

float hr_get_(void)
{
	/**
	 * 取 0.9Hz到3.33Hz之间的幅度最大的频点，对应心率值54-200
	 * 0.9Hz(hr = 54)  -> (60000/54=1111ms -> 1111ms/1250ms -> 0.9Hz )
	 * 3.33Hz(hr=200) -> (60000/200=300ms -> 1000ms/300ms -> 3.33Hz )	
	 */	

	float frecency = get_max_frecency(0.9f, 3.33f);
	
	return (float)(60000.0f/(1000.0f/frecency));
}

float hr_array[5] = {75.0f,75.0f,75.0f,75.0f,75.0f};
float hr_real;
	
float hr_get(void)
{
	float temp;
	int d4l;
	
	hr_array[0] = hr_array[1];
	hr_array[1] = hr_array[2];
	hr_array[2] = hr_array[3];
	hr_array[3] = hr_array[4];
	/* hr_real = */ temp = hr_get_();
	hr_real = 75*0.75f + temp*0.25f;  // 优化为权重比方式，实际心率占25%
	
	d4l = abs( (int)temp - (int)hr_array[4] );
	if ( (int)temp > (int)hr_array[4] )
	{
		if ( d4l > 25 )
		{
			hr_array[4] += d4l/2;
		} else
		{
			hr_array[4] = temp;		
		}		
	}else
	{
		if ( d4l > 25 )
		{
			hr_array[4] -= d4l/2;
		} else
		{
			hr_array[4] = temp;		
		}		
	}

	return ((hr_array[0]+hr_array[1]+hr_array[2]+hr_array[3]+hr_array[4])/5.0f);
}

void hr_reset(float hr)
{
	for ( int i = 0; i < SIZEOF(hr_array); i++ )
	{
		hr_array[i] = hr;
	}
}

void do_hr(void)
{

	/** 在此也可以对hr.hr的值做最后一次验证 */

	/** 
	 * 动态心率、血压补偿. 当前实际心率作为基础心率，
	 * 根据运动进行血压补偿.
	 */
	unsigned long pressure;

	heart_set_base_heart(hr.hr); 
	// hr.hr = heart_get_comp_val();
	pressure = heart_get_comp_blood_pressure_val(hr.hr);
	hr.hp = pressure>>8;
	hr.lp = pressure & 0xFF; 

	float temp = heart_get_comp_spo2(hr.hr);

	hr.spo2 = (temp>99.9999f)?(99.99999f):(temp);
}

unsigned int leave_time,leaveFlag = 0;
unsigned char hr_reset_flag = 0;
unsigned char upload_flag = 0;

unsigned long taskHr( unsigned long task_id, unsigned long events )
{ 
	if ( events & TASK_HR_STOP_EVT )
	{
		hr_clock_rtc_stop();
		hr_pwr_enable(false);
		HR_ADC_PIN_OUTPUT_LOW();
		nrf_saadc_disable();
		sleepEnable = 1;
		
		/* 自动测量模式，马达静默 */
		if ( hr.auto_flag != 1 )
		{
			osal_set_event ( taskMotorTaskId, TASK_MOTOR_VIBORATE_EVT );
		}
		
		hr.auto_flag = 0;			
		
		hr.stop = 1; to_close = 0;
		leave_time = 0; leaveFlag = 0;
		
		osal_start_timerEx( taskUploadTaskId, TASK_UPLOAD_HR_DONE_EVT, 4000);
		
		#if 0
		if ( config.test_mdoe == 0x1 )
		{  
			/** 测试模式下心率值不处于60-95之间或者脱手则提示错误,2s后继续测试 
			 *  否则说明测试成功,1秒后将config.mode写入Flash,并显示OK.
			 */
			if ( hr.hr < 60 || hr.hr > 100 )
			{
				hr.error = 1;
			}
			
			if ( hr.error == 1 )
			{
				osal_start_timerEx( task_id, TASK_HR_START_EVT, 2000);
			}else{
				osal_set_event( task_id, TASK_HR_SENSOR_OK_EVT );
			}
			
			win_ticks = 0;// 确保测试模式不会灭屏			
		}	
		#endif		
		
		return ( events ^ TASK_HR_STOP_EVT );
	}
	
	if ( events & TASK_HR_START_EVT )
	{
		hr_clock_rtc_start();
		hr_pwr_enable(true);
		sleepEnable = 0;
		
		fft_reset();
		hr_reset_flag = 1;
		
		hr.stop = 0;
		dect_mTicks = hr_mticks;
		hr_showFlag = 1;
		hr.fg = 0;
		upload_flag = 1;
		
		hr.stat = HR_DECT_STAT_DECTING;
		
		/* 自动测量模式，马达静默 */
		if ( hr.auto_flag != 1 )
		{
			osal_set_event ( taskMotorTaskId, TASK_MOTOR_VIBORATE_EVT );
		}
		// 8秒稳定后再进行检测,稳定时间由硬件决定.
		
		leaveEnable = false;
		osal_start_timerEx( task_id, TASK_HR_LEAVE_EVT, 4000); 
		
		osal_start_timerEx( task_id, TASK_HR_NORMAL_EVT, 100 );
		
		return ( events ^ TASK_HR_START_EVT );
	}
	
	if ( events & TASK_HR_LEAVE_EVT )
	{
		/**
		 * 运放模块稳定后2.1秒在闪动心率图标,避免与2秒脱腕检测时间冲突.
		 */
		leaveEnable = true; /* 使能脱腕检测 */
		
		dect_mTicks = hr_mticks;
		
		return ( events ^ TASK_HR_LEAVE_EVT );
	}
	
	if ( events & TASK_HR_NORMAL_EVT )
	{
		if ( hr.stat == HR_DECT_STAT_DECTING )
		{
			dect_mTicks = hr_mticks;
			
			hr.stat = HR_DECT_STAT_NORMAL; /* 进入正常检测模式, 允许图标闪动 */			
		}
		
		return ( events ^ TASK_HR_NORMAL_EVT );
	}
				
	if ( events & TASK_HR_SAMPLE_EVT )
	{
		if ( config.hrWaveUploadEnable == 1 )
		{
			Debug_ble_send_hex(current_hr_adc);
		}
		
		leave_array_put( current_hr_adc );
		
		#if 1
		if ( current_touch_adc < hr.touch_level )
		{
			// 2s Detecting time
			leave_time++;
			if ( leave_time > 50 )
			{
				leaveFlag = 1;
			}
		}else{
			leave_time = 0;
		}
		#endif
		
		#if 1
        if ( (leaveEnable == true && is_leave() == true) || 
            ( (leaveEnable == true) && (leaveFlag == 1) )  )
		{	
			if ( hr.stat == HR_DECT_STAT_DONE )
			{
				hr.stat = HR_DECT_STAT_STOP;
			}else{
				hr.stat = HR_DECT_STAT_ERROR;
			}
			
			hr.leave_flag = 1;
				
			osal_set_event( task_id, TASK_HR_STOP_EVT ); 
			
			return ( events ^ TASK_HR_SAMPLE_EVT );
		}
		#endif
			
		// if ( (hr_mticks - dect_mTicks) > 60000 )/* Note FFT 20480 Point */
		// 时间缩短为20秒(5x4s),刚好将滤波数组填充满; 2017.11.16
		// 增加2s 2017.11.23
		if ( (hr_mticks - dect_mTicks) > 35000 )/* Note FFT 20480 Point */
		{
			/**
			 * FFT采样频率为50Hz, 采样点数为1024点,
			 * 共需要1024*1/50s=20.48s的时间.
			 * 为使得尽快出心率,可以采集少于20.48s.
			 */    
			hr.stat = HR_DECT_STAT_STOP;
			osal_set_event( task_id, TASK_HR_STOP_EVT );

			/** 
			 * The automatic measurement mode stores only one data
			 */
			if ( hr.auto_flag == 1 )
			{
				osal_set_event( task_id, TASK_HR_DECT_DONE_HR_EVT );
			}
			
			hr.leave_flag = 0;			
			
			return ( events ^ TASK_HR_SAMPLE_EVT );
		} 
		
		if ( ( (hr_mticks - dect_mTicks) > need_mTicks ) && (hr.fg == 0) )
		{
			/**
			 * 开始进行FFT运算 (每隔4秒)
			 * 第一个心率出来后,用该值填充hr_array数组.
			 * 如果心率值与上一次不等,则保存并上传.
			 * 血压和血氧上传规则与心率保持一致.
			 */
			hr.fg = 1;  hr.stat = HR_DECT_STAT_DONE;
			
			fft();								
			float temp = (int)hr_get();
			
			upload_flag++;
			
			if ( hr_reset_flag == 1 )
			{
				hr_reset(hr_real);
				temp = hr_real;
				hr_reset_flag = 0;
			}			
			
			if ( ((int)hr.hr != (int)temp ) || !(upload_flag % 2) )
			{
				do_hr();
				
				osal_set_event ( task_id, TASK_HR_DECT_DONE_HR_UPLOAD_EVT );
			}
			
			/** 
			 * The automatic measurement mode stores only one data
			 */			
			if ( ( ( (int)hr.hr != (int)temp ) || !(upload_flag % 4) )
					&& hr.auto_flag != 1 )
			{
				osal_set_event( task_id, TASK_HR_DECT_DONE_HR_EVT );
			}
			
			hr.hr = temp;
			osal_start_timerEx( task_id, TASK_HR_FFT_ENABLE_EVT, 4000);
		}		
			
		return ( events ^ TASK_HR_SAMPLE_EVT );
	}
	
	if ( events & TASK_HR_FFT_ENABLE_EVT )
	{
	    hr.fg = 0;
		
		return ( events ^ TASK_HR_FFT_ENABLE_EVT );
	}		
				
	if ( events & TASK_HR_DECT_DONE_HR_EVT )
	{
		/** 保存当前心率血压血氧值 */
		
		osal_set_event( taskStoreTaskId, TASK_STORE_SAVE_HR_EVT ); 
		osal_start_timerEx( taskStoreTaskId, TASK_STORE_SAVE_SPO2_EVT,800);
		osal_start_timerEx( taskStoreTaskId, TASK_STORE_SAVE_B_PRESSURE_EVT, 1600);		

		return ( events ^ TASK_HR_DECT_DONE_HR_EVT );
	}
	
	if ( events & TASK_HR_DECT_DONE_HR_UPLOAD_EVT )
	{
		/** 上传当前心率血压血氧值 */
		
		osal_set_event( taskUploadTaskId, TASK_UPLOAD_iBand_HR_DECT_EVT );
		osal_start_timerEx( taskUploadTaskId, TASK_UPLOAD_iBand_B_PRUESSURE_EVT, 75 );		
		osal_start_timerEx( taskUploadTaskId, TASK_UPLOAD_iBand_SPO2_EVT, 150 );
		
		return ( events ^ TASK_HR_DECT_DONE_HR_UPLOAD_EVT );
	}
	
#if (OTA_MODE_ENABLE==0)	
	
	if ( events & TASK_HR_SENSOR_OK_EVT )
	{		
		if ( (nrf_gpio_pin_read(HR_ADC_PIN) == 1) &&
			(nrf_gpio_pin_read(HR_TOUCH_LEVEL_PIN) == 1) )
		{
			hr.ok = 1;
		}else{
            hr.ok = 0;
        }
		
		if ( hr.ok == 1  )
		{
			osal_start_timerEx( task_id, TASK_HR_SENSOR_COMFIR_EVTT, 50);
		}else{
			osal_start_timerEx( task_id, TASK_HR_PW_ENABLE_EVT, 250);
		}
		
		hr_pwr_enable(false);
		
		return ( events ^ TASK_HR_SENSOR_OK_EVT );
	}	
	
	if ( events & TASK_HR_SENSOR_COMFIR_EVTT )
	{
		hr_ok = 1;		
		return ( events ^ TASK_HR_SENSOR_COMFIR_EVTT );
	}
	
	if ( events & TASK_HR_PW_ENABLE_EVT )
	{
		if ( config.test_mdoe == 1 )
		{
			nrf_gpio_pin_pull_t config_1 = NRF_GPIO_PIN_PULLDOWN;
			nrf_gpio_cfg_input(HR_ADC_PIN, config_1);
			
			nrf_gpio_pin_pull_t config_2 = NRF_GPIO_PIN_PULLDOWN;
			nrf_gpio_cfg_input(HR_TOUCH_LEVEL_PIN, config_2);			
			hr_pwr_enable(true);
			
			osal_start_timerEx( task_id, TASK_HR_SENSOR_OK_EVT, 500);
		}
		
		return ( events ^ TASK_HR_PW_ENABLE_EVT );
	}
#endif
		
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
	
	nrf_gpio_cfg(
            HR_PWR_PIN,
            NRF_GPIO_PIN_DIR_OUTPUT,
            NRF_GPIO_PIN_INPUT_DISCONNECT,
            NRF_GPIO_PIN_PULLUP,
            NRF_GPIO_PIN_S0S1,
            NRF_GPIO_PIN_NOSENSE);
	nrf_gpio_pin_set(HR_PWR_PIN);	
	
	hr_clock_rtc_init();	
	fft_init();
		
	HR_ADC_PIN_OUTPUT_LOW();
	
#if (OTA_MODE_ENABLE==0)	
	hr.ok = 0;
	osal_start_timerEx( task_id, TASK_HR_PW_ENABLE_EVT, 250);
#endif
}
