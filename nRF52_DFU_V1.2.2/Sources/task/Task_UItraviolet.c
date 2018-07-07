/*******************************************************************************
* Copytight 2016 Mandridy Tech.Co., Ltd. All rights reserved                   *
*                                                                              *
* Filename : OSAL_TaskDemo.c                                                   *
* Author : Wen Shifang                                                         *
* Version : 1.0                                                                *
*                                                                              *
* Decription : A simple Task instance for OSAL                                 *
* Function-list:                                                               *
* History:                                                                     *
*       <author>     <time>     <version>  <desc>                              *
*       Wen Shifang  2017-3.30  1.0        build this moudle                   *
*                                                                              *
*                                                                              *
* Created : 2017-3-30                                                          *
* Last modified : 2017.3.30                                                    *
*******************************************************************************/

#include "Task_UItraviolet.h"
#include "OSAL.h"
#include "OSAL_Task.h"
#include "OSAL_Timer.h"

#include "SSADC.h"
#include "UI_win_notify.h"
#include "ClockTick.h"
#include "Task_Store.h"
#include "Task_Flash.h"

static nrf_saadc_value_t  saadc_buff[SAADC_BUFF_SISE];


static void saadc_init__(void)
{
	nrf_saadc_channel_config_t   nrf_saadc_channel_config;
	
	nrf_saadc_disable();
	
	/* Positive channel resistor control 阻抗*/
	nrf_saadc_channel_config.resistor_p = NRF_SAADC_RESISTOR_DISABLED;
	nrf_saadc_channel_config.resistor_n = NRF_SAADC_RESISTOR_DISABLED;
	/* Gain factor of the analog-to-digital converter input 增益*/
	nrf_saadc_channel_config.gain       = NRF_SAADC_GAIN1_2; 
	/* Reference selection,Internal reference (0.6 V). 参考电压*/
	nrf_saadc_channel_config.reference  = NRF_SAADC_REFERENCE_INTERNAL;
	/*Analog-to-digital converter acquisition time 采集时间 */
	nrf_saadc_channel_config.acq_time   = NRF_SAADC_ACQTIME_20US;
	/*  Single ended, PSELN will be ignored, negative input to ADC shorted to GND. */
	nrf_saadc_channel_config.mode       = NRF_SAADC_MODE_SINGLE_ENDED;
	/* Input selection for the analog-to-digital converter.引脚选择 */
	nrf_saadc_channel_config.pin_p      = UITR_ADC_PIN;
	nrf_saadc_channel_config.pin_n      = NRF_SAADC_INPUT_DISABLED;
	nrf_saadc_channel_init(0, &nrf_saadc_channel_config);	
	
	/*14位ADC */
	nrf_saadc_resolution_set(NRF_SAADC_RESOLUTION_12BIT);
	
	
//	NRF_SAADC->SAMPLERATE = ( (160<<0)
//	                         | (0<<12)
//							);
							
	nrf_saadc_int_disable(NRF_SAADC_INT_END);
	
	/* Function for enabling the SAADC. */
	nrf_saadc_enable();
}

static nrf_saadc_value_t* saadc_buffer_convert__(void)
{
	// nrf_saadc_channel_input_set(0, BAT_DET_ADC_PIN, NRF_SAADC_INPUT_DISABLED);
	
	#if 1	
	/* initializing the SAADC result buffer */
	nrf_saadc_buffer_init(saadc_buff, 1);
	
	nrf_saadc_task_trigger(NRF_SAADC_TASK_START);
    nrf_saadc_task_trigger(NRF_SAADC_TASK_SAMPLE);
	
	uint32_t timeout = 1000000;
    while (0 == nrf_saadc_event_check(NRF_SAADC_EVENT_END) && timeout > 0)
    {
        timeout--;
    }
	#endif
	
	nrf_saadc_event_clear(NRF_SAADC_EVENT_END);
	
	return saadc_buff;
}

unsigned long taskUItravioletTaskId;

short UIT_adc = 0;
float UIT_vol;

float UIT_cm2;
float UIT_i;
float UIT_cm2_save[2];
float UIT_i_save[2];

#include <math.h>
#include "btprotocol.h"


// 电压转 mw/cm2

#define       p1        -1538  
#define       p2         2690  
#define       p3        273.2   
#define       p4        -3507  
#define       p5         2952   
#define       p6        -1050   
#define       p7        168.1   
#define       p8       -3.305   
#define       p9       0.3219   

float v_to_cm2 ( float vol )
{

    float cm2 = p1 * pow(vol,8) + p2*pow(vol,7) + p3*pow(vol,6) + p4*pow(vol,5) + 
                    p5*pow(vol,4) + p6*pow(vol,3) + p7*pow(vol,2) + p8*vol + p9;
    
    return cm2;
}

// mw/cm2 转 紫外线等级
#define       p11     -0.00359  
#define       p12      0.08089  
#define       p13       -0.747   
#define       p14        3.647   
#define       p15       -10.15   
#define       p16        16.29   
#define       p17       -14.25   
#define       p18        6.701   
#define       p19       -1.118

float cm_to_i( float cm2 )
{
    float i = p11*pow(cm2,8) + p12*pow(cm2,7) + p13*pow(cm2,6) + p14*pow(cm2,5) + 
                    p15*pow(cm2,4) +
    p16*pow(cm2,3) +
    p17*pow(cm2,2) + 
    p18*pow(cm2,1) + p19;
    
    return i;
}

struct map_cm2_to_level
{
  float idx;
  float level;
};

struct map_cm2_to_level map_2[]=
{
{0.0,0.000f},
{0.1,0.250f},
{0.2,0.625f},
{0.3,0.750f},
{0.4,0.875f},
{0.5,1.000f},
{0.6,1.125f},
{0.7,1.250f},
{0.8,1.375f},
{0.9,1.500f},
{1.0,1.550f},
{1.1,1.600f},
{1.2,1.650f},
{1.3,1.700f},
{1.4,1.875f},
{1.5,7.937f},
{1.6,2.000f},
{1.7,2.062f},
{1.8,2.125f},
{1.9,2.250f},
{2.0,2.312f},
{2.1,2.375f},
{2.2,2.500f},
{2.3,2.531f},
{2.4,2.562f},
{2.5,2.590f},
{2.6,2.625f},
{2.7,2.675f},
{2.8,2.700f},
{2.9,2.725f},
{3.0,2.750f},
{3.1,2.850f},    
{3.2,2.920f},
{3.3,3.000f},
{3.4,3.050f},
{3.5,3.100f},
{3.6,3.150f},
{3.7,3.200f},
{3.8,3.250f},
{3.9,3.271f},
{4.0,3.312f},
{4.1,3.333f},
{4.2,3.354f},
{4.3,3.375f},
{4.4,3.393f},
{4.5,3.420f},
{4.6,3.445f},
{4.7,3.465f},
{4.8,3.478f}, 
{4.9,3.485f},
{5.0,3.500f},
{5.1,3.535f},
{5.2,3.571f},
{5.3,3.607f},
{5.4,3.642f},
{5.5,3.678f},
{5.6,3.714f},
{5.7,3.750f},
{5.8,3.785f},
{5.9,3.821},
{6.0,3.857f},
{6.1,3.892f},
{6.2,3.928f},
{6.3,3.754f},
{6.4,4.000f},
{6.5,4.035f},
{6.6,4.071f},
{6.7,4.107f},
{6.8,4.142f},
{6.9,4.178f},
{7.0,4.214f},
{7.1,4.250f},
{7.2,4.275f},
{7.3,4.300f},
{7.4,4.352f},
{7.5,4.350f},
{7.6,4.375f},
{7.7,4.400f},
{7.8,4.425f},
{7.9,4.450f},
{8.0,4.475f},
{8.1,4.500f},
{8.2,4.522f},
{8.3,4.545f},
{8.4,4.568f},
{8.5,4.590f},
{8.6,4.613f},
{8.7,4.636f},
{8.8,4.659f},
{8.9,4.681f},
{9.0,4.704f},
{9.1,4.727f},
{9.2,4.750f},
{9.3,4.769},
{9.4,4.788},
{9.5,4.807},
{9.6,4.826},
{9.7,4.846},
{9.8,4.865},
{9.9,4.884},
{10.0,4.903},
{10.1,4.922},
{10.2,4.941},
{10.3,4.960},
{10.4,4.979},
{10.5,5.000},
{10.6,5.031},
{10.7,5.062},
{10.8,5.093},
{10.9,5.125},
{10.0,5.156},
{11.1,5.187},
{11.2,5.218},
{11.3,5.250},
};

/** 
 * 二分查找法，找到对应ADC值的数组下标 
 * 注意：原数据为逆序存放，经典二分查找算法要修改一下。
 */
static int get_index_i(float level)
{
	float min = level-map_2[0].idx;
	if ( min < 0 ) min *= -1;
	
	int idx = 0;
	
	for ( int i = 0; i < (sizeof(map_2)/sizeof(map_2[0])); i++ )
	{
		float temp = level-map_2[i].idx;
		if ( temp < 0 ) temp *= -1;
		if ( min > temp )
		{
			min = temp;
			idx = i;
		}
	}
    
    /* 若没有查找到，则返回最临近的 */
    return idx;
}

/**
 * 根据下标在温度值数组中取得对应温度值。
 */
static float getTvalue_i(int index)
{ 
  return map_2[index].level;
}
   

/**
* 外部调用接口
*/
float get_uit_level(float level)
{
    int idx;
    
    idx = get_index_i( level );
    
    return getTvalue_i(idx);
}


/////////////////////////////////////////////////////
struct MAP_TAG
{
    int uit_level;
    float vol;
};

struct MAP_TAG map_3[]=
{
{0,0.0f},
{1,10.0f},
{2,90.0f},
{3,129.0f},
{4,161.0f},
{5,198.0f},
{6,235.0f},
{7,279.0f},
{8,296.0f},
{9,326.0f},
{10,398.0f},
{11,437.0f},
{12,489.0f},
};

/** 
 * 二分查找法，找到对应ADC值的数组下标 
 * 注意：原数据为逆序存放，经典二分查找算法要修改一下。
 */
static int get_index_ii(float vol)
{
	float min = vol-map_3[0].vol;
	if ( min < 0 ) min *= -1;
	
	int idx = 0;
	
	for ( int i = 0; i < (sizeof(map_3)/sizeof(map_3[0])); i++ )
	{
		float temp = vol-map_3[i].vol;
		if ( temp < 0 ) temp *= -1;
		if ( min > temp )
		{
			min = temp;
			idx = i;
		}
	}
    
    /* 若没有查找到，则返回最临近的 */
    return idx;
}

/**
 * 根据下标在温度值数组中取得对应温度值。
 */
static float getTvalue_ii(int index)
{ 
  return map_3[index].uit_level;
}
   

/**
* 外部调用接口
*/
float get_uit_level_ex(float vol)
{
    int idx;
    
    idx = get_index_ii( vol );
    
    return getTvalue_ii(idx);
}

/////////////////////////////////////////////////////

int UIT_adcs[3] = {0};
int dangerius_cnt = 0;
#define MAX_UIT     2
unsigned char uit_notify_enable;
unsigned char uit_warnning_enable;
unsigned char uit_warnning_val = MAX_UIT;
unsigned char uit_warnning_interval = 2;
unsigned char dataCnt = 0;
long sampleCnt = 0;

unsigned char local_tx[20];

unsigned long taskUItraviolet( unsigned long task_id, unsigned long events )
{
	if ( events  &  TASK_UITRAVIOLET_START_EVT )
	{      
        short * p_adc_value;
            
        saadc_init__();
        
		p_adc_value = saadc_buffer_convert__();
		if ( (short)(p_adc_value[0]) < 0 ){
			p_adc_value[0] = 0;
		}
		if ( (short)(p_adc_value[0]) > 4095 )
		{
			p_adc_value[0] = 4095;
		}        
        
        UIT_adc = p_adc_value[0];
        UIT_adcs[0] = UIT_adcs[1];
        UIT_adcs[1] = UIT_adcs[2];
        UIT_adcs[2] = UIT_adc;
        
        UIT_adc = (UIT_adcs[0]+UIT_adcs[1]+UIT_adcs[2])/3;
        
        /** 求电压 */
        UIT_vol = UIT_adc * (0.6f/4096.0f) * 2;
        
        UIT_i = get_uit_level_ex(UIT_vol*1000);
        UIT_cm2 = get_uit_level(UIT_i);
        
        if ( UIT_i > uit_warnning_val && (uit_warnning_enable == 1) )
        {
            dangerius_cnt++;
            
            /**
             * 持续uit_warnning_interval分钟超过提醒阈值,则报警提示
             */
            if ( dangerius_cnt > uit_warnning_interval*60 ) 
            {
                dangerius_cnt = 0;

                NOTICE_ADD( NOTIFY_ID_UIT );
            }
        }else{
            dangerius_cnt = 0;
        }        

        /* 更新每半个小时的最大最小值 */
        if ( UIT_cm2 > UIT_cm2_save[0] )
        {
            UIT_cm2_save[0] = UIT_cm2;
        }
        
        if ( UIT_i_save[0] > UIT_i )
        {
            UIT_i_save[0] = UIT_i;
        }
        
        sampleCnt++;

        osal_start_timerEx ( task_id, TASK_UITRAVIOLET_START_EVT, 1000 );
        
        if ( (uit_notify_enable & 0x1 ) && !( sampleCnt % 5) ) /** 5秒上传一次 */
        {
            osal_set_event ( task_id, TASK_UIT_UPDATE_UV_EVT );
        }
               
        if ( ((sampleCnt % 3600) == 0 ) && (TimerHH() >= 6) && (TimerHH() < 18) )         /* 每个60分钟上报一次 */
        {            
        }
        
		return ( events ^ TASK_UITRAVIOLET_START_EVT );
	}
    
    if ( events & TASK_UIT_UPDATE_UV_EVT )
    {
        unsigned char *p = (unsigned char *)&UIT_cm2;
        
        local_tx[0] = 0x28;
        local_tx[1] = 0x00;
        local_tx[2] = (int)UIT_i;
        local_tx[3] = p[3];
        local_tx[4] = p[2];
        local_tx[5] = p[1];
        local_tx[6] = p[0];
        
        bt_protocol_tx( local_tx, sizeof(local_tx));
        
        return ( events ^ TASK_UIT_UPDATE_UV_EVT );
    }
    
    if ( events & TASK_UIT_SAVE_UIT_EVT )
    {
        /* 6-18点: 30分钟保存1个,1次保存2个,60分钟1组 */
        
        if ( (TimerHH() >= 6) && (TimerHH() <= 18) )       
        {
            osal_set_event ( taskStoreTaskId, TASK_STORE_SAVE_UVT_EVT ); 
            
            local_tx[0] = 0x28;
            local_tx[1] = 0x02;
            local_tx[2] = fm.erea[FMC_ID_UIT].items;     

            bt_protocol_tx( local_tx, sizeof(local_tx));                 
        }
        
        return ( events ^ TASK_UIT_SAVE_UIT_EVT );
    }
	
	if ( events & TASK_UITRAVIOLET_STOP_EVT )
	{
		return ( events ^ TASK_UITRAVIOLET_STOP_EVT );
	}
    
    if ( events & TASK_UITRAVIOLET_INIT_EVET )
    {
        osal_set_event ( task_id, TASK_UITRAVIOLET_START_EVT );
        
        return ( events ^ TASK_UITRAVIOLET_INIT_EVET );
    }
	
	return ( 0 );
}

void taskUItravioletInit( unsigned long task_id )
{
	taskUItravioletTaskId = task_id;
	
    osal_set_event( task_id, TASK_UITRAVIOLET_INIT_EVET );
}

