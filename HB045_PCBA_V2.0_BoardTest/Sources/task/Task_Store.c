#include "string.h"
#include <time.h>

#include "OSAL.h"
#include "OSAL_Timer.h"
#include "Task_Step.h"
#include "Task_Upload.h"
#include "Task_Flash.h"
#include "Task_Store.h"
#include "Task_Ble.h"

#include "ClockTick.h"
#include "btprotocol.h"
#include "UserSetting.h"
#include "Log.h"

unsigned long taskStoreTaskId;

unsigned long taskStore (unsigned long task_id, unsigned long events )
{
	static unsigned char txbuf[20]  = {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};
	
	unsigned long utc;
	
    /**
     *  Save the Heart Rate data to flash memory
     */
    if ( events & TASK_STORE_SAVE_HR_EVT )
    {
		// Heart Rate Data Formate
		// YY MM DD hh mm ss Hr 00 00 00 00 00 00 00 00 00
		
        memset( txbuf, 0x00, sizeof(txbuf) );
        
        txbuf[0]  = DECToBCD(TimerYY());
        txbuf[1]  = DECToBCD(TimerMM());
        txbuf[2]  = DECToBCD(TimerDD());
        txbuf[3]  = DECToBCD(TimerHH());
        txbuf[4]  = DECToBCD(TimerMI());
        txbuf[5]  = DECToBCD(TimerSE());
        		
		txbuf[6] = hr.hr;
		// flash_memory_put( FM_ID_HR, (unsigned char*)txbuf, 16);
		flash_temp_queue_put( FM_ID_HR, (unsigned char*)txbuf, 16);
		
        return ( events ^ TASK_STORE_SAVE_HR_EVT );
    }
	
    /**
     *  Save the Blood Pressure to flash memory
     */	
	if ( events & TASK_STORE_SAVE_B_PRESSURE_EVT )
	{
		// Blood Pressure Data Formate
		// YY MM DD hh mm ss HP LP HR 00 00 00 00 00 00 00

        memset( txbuf, 0x00, sizeof(txbuf) );
        
        txbuf[0]  = DECToBCD(TimerYY());
        txbuf[1]  = DECToBCD(TimerMM());
        txbuf[2]  = DECToBCD(TimerDD());
        txbuf[3]  = DECToBCD(TimerHH());
        txbuf[4]  = DECToBCD(TimerMI());
        txbuf[5]  = DECToBCD(TimerSE());
		
		txbuf[6] = hr.hp;
		txbuf[7] = hr.lp;
		txbuf[8] = hr.hr;
		
		// flash_memory_put( FM_ID_B_PRESSURE, (unsigned char*)txbuf, 16);
		flash_temp_queue_put(FM_ID_B_PRESSURE, (unsigned char*)txbuf, 16);

		return ( events ^ TASK_STORE_SAVE_B_PRESSURE_EVT );
	}
	
	/**
	 * Save the spo2 to flash memory
	 */
	if ( events & TASK_STORE_SAVE_SPO2_EVT )
	{
		// SPO2 Data Formate
		// YY MM DD hh mm ss O2 00 00 00 00 00 00 00 00 00
		
        memset( txbuf, 0x00, sizeof(txbuf) );
        
        txbuf[0]  = DECToBCD(TimerYY());
        txbuf[1]  = DECToBCD(TimerMM());
        txbuf[2]  = DECToBCD(TimerDD());
        txbuf[3]  = DECToBCD(TimerHH());
        txbuf[4]  = DECToBCD(TimerMI());
        txbuf[5]  = DECToBCD(TimerSE());
		
        txbuf[6] = (unsigned char)(hr.spo2);
        txbuf[7] = (unsigned char)((hr.spo2 - (unsigned char)(hr.spo2)) *10);
		txbuf[8] = 0;		

		// flash_memory_put( FM_ID_SPO2, (unsigned char*)txbuf, 16);
		flash_temp_queue_put( FM_ID_SPO2, (unsigned char*)txbuf, 16);
		
		return ( events ^ TASK_STORE_SAVE_SPO2_EVT );
	}
	
	/**
	 * 保存计步数据(废弃)
	 */
    if ( events & TASK_STORE_SAVE_PEDO_EVT )
    {
        // Foramt 0xYY MM DD HH MI SE CO CO CO CA CA CA DI DI DI 00 00 00 00 00
		
		osal_set_event ( taskStepTaskId, TASK_STEP_CLEAR_ALL_EVT );
		
		osal_start_timerEx( taskUploadTaskId, TASK_UPLOAD_PEDO_EVT, 100);
		
        return ( events ^ TASK_STORE_SAVE_PEDO_EVT );
    }
	    
	/** 
	 * 保存分段计步数据
	 */
	if ( events & TASK_STORE_SAVE_SEG_PEDO_EVT )		
	{
        // Foramt 0xCO CO CO CA CA CA DI DI DI t1 t2 t3 t4 cn 00 00
		
		unsigned long utc;
		
		utc = getUTC() - 3600;
		
        memset( txbuf, 0x00, sizeof(txbuf) );
		
		unsigned long temp;
	
		if ( pedometer.counter > pedometer_last.counter )
		{
			temp = pedometer.counter - pedometer_last.counter;
			if ( temp > 99999 )
			{
				return ( events ^ TASK_STORE_SAVE_SEG_PEDO_EVT );
			}			
			txbuf[0]  = (temp >> 16) & 0xFF;
			txbuf[1]  = (temp >>  8) & 0xFF;
			txbuf[2]  = (temp >>  0) & 0xFF;
		}
		if ( pedometer.calorie > pedometer_last.calorie )
		{
			temp = pedometer.calorie - pedometer_last.calorie;
			if ( temp > 99999 )
			{
				return ( events ^ TASK_STORE_SAVE_SEG_PEDO_EVT );
			}			
			txbuf[3] = (temp >> 16) & 0xFF;
			txbuf[4] = (temp >>  8) & 0xFF;
			txbuf[5] = (temp >>  0) & 0xFF;
		}
		if ( pedometer.distance > pedometer_last.distance )
		{
			temp = pedometer.distance - pedometer_last.distance; 
			if ( temp > 99999 )
			{
				return ( events ^ TASK_STORE_SAVE_SEG_PEDO_EVT );
			}			
			txbuf[6] = (temp >> 16) & 0xFF;
			txbuf[7] = (temp >>  8) & 0xFF;
			txbuf[8] = (temp >>  0) & 0xFF;
		}
		
		txbuf[9] = (utc>>24) & 0xFF;
		txbuf[10] = (utc>>16) & 0xFF;
		txbuf[11] = (utc>>8) & 0xFF;
		txbuf[12] = (utc>>0) & 0xFF;
		txbuf[13] = 0x3C;
		
		pedometer_last.counter = pedometer.counter;
		pedometer_last.calorie = pedometer.calorie;
		pedometer_last.distance = pedometer.distance;
		
		// flash_memory_put( FM_ID_SEG_PEDO, (unsigned char*)txbuf, 16);
		flash_temp_queue_put( FM_ID_SEG_PEDO, (unsigned char*)txbuf, 16);
		
		return ( events ^ TASK_STORE_SAVE_SEG_PEDO_EVT );
	}
	
    if ( events & TASK_STORE_UPLOAD_RUNNING_EVT )
    {
        // 一次运动结束,上传,以便通知APP读取  (使用iBand)      
        // 上报协议格式 0x1B EN SS 00 00 00 D6 D5 D4 D3 D2 D1 D0 U3 U2 U1 U0 TH TL CRC
        
        memset( txbuf, 0, sizeof(txbuf) );
       
        txbuf[0] = 0x1B;
        txbuf[1]  = 3; // EN[3:0]--> 3 当前数据上报
        txbuf[2]  = 0; // SS
        
        bt_protocol_tx( txbuf, sizeof(txbuf) );      
      
        return ( events ^ TASK_STORE_UPLOAD_RUNNING_EVT );
    }	
	
	if ( events &  TASK_STORE_SAVE_BYCLE_EVT )
	{
        // 运动数据-自行车     
        // 保存格式 0xEN SS D6 D5 D4 D3 D2 D1 D0 U3 U2 U1 U0 TH TL CRC
        
        memset( txbuf, 0x00, sizeof(txbuf) );
        
        utc = getUTC();
        unsigned long len = (utc - config.train_bycle_utc)/60;
        utc = config.train_bycle_utc;
        unsigned long va = pedometer.counter - config.train_bycle_pedometer;
        unsigned long vb = pedometer.calorie - config.train_bycle_calorie;
        unsigned long vc = pedometer.distance - config.train_bycle_distance;
        
        if ( vb == 0 )
        {
           return ( events ^ TASK_STORE_SAVE_BYCLE_EVT );
        }
      
        txbuf[0]  = (0x1<<4) | 0; // EN[7:4]--> 1 骑行
        txbuf[1]  = 0x0 | (0x1<<3);    // SS[3] --> 1 卡路里有效
        txbuf[2]  = (va>>14) & 0x7;     /* D6D5...D0 */
        txbuf[3]  = (va>>6) & 0xFF;
        txbuf[4]  = ((va&0x3F)<<2)|((vb>>15)&0x3);
        txbuf[5]  = (vb>>7) & 0xFF;
        txbuf[6]  = ((vb&0x7F)<<1) | ((vc>>16)&0x1);
        txbuf[7]  = (vc>>8) & 0xFF;
        txbuf[8]  = vc & 0xFF;
        txbuf[9]  = utc>>24;             /* U3U2...U0 */
        txbuf[10] = utc>>16;             
        txbuf[11] = utc>>8;              
        txbuf[12] = utc & 0xFF;  
        txbuf[13] = len>>8;              /* TH */
        txbuf[14] = len & 0xFF;          /* TL */
        txbuf[15] = 0xFF;                /* CRC */;
        
        // flash_memory_put( FMC_ID_RUNNING, txbuf, 16); 
		flash_temp_queue_put( FMC_ID_RUNNING, txbuf, 16); 
        
        osal_start_timerEx( task_id, TASK_STORE_UPLOAD_RUNNING_EVT, 800);
		
		return ( events ^ TASK_STORE_SAVE_BYCLE_EVT );
	}
	
	if ( events & TASK_STORE_SAVE_RUNNING_EVT )
	{
        // 运动数据-跑步-慢走快走      
        // 保存格式 0xEN SS D6 D5 D4 D3 D2 D1 D0 U3 U2 U1 U0 TH TL CRC
        
        memset( txbuf, 0x00, sizeof(txbuf) );
        
        utc = getUTC();
        int len = (utc - config.train_running_utc)/60;
        utc = config.train_running_utc;
        unsigned long va = pedometer.counter - config.train_running_pedometer;
        unsigned long vb = pedometer.calorie - config.train_running_calorie;
        unsigned long vc = pedometer.distance - config.train_running_distance;
        
        if ( va == 0 )
        {
           return ( events ^ TASK_STORE_SAVE_RUNNING_EVT );
        }
      
        txbuf[0]  = 0x0<<4 | 0; // EN[7:4]--> 0 步行
        txbuf[1]  = (0x0<<0) | (0x7<<2); // SS[1:0]--> 0 慢走 SS[2：4]-->7 卡路里、里程和步数都有效
        txbuf[2]  = (va>>14) & 0x7;     /* D6D5...D0 */
        txbuf[3]  = (va>>6) & 0xFF;
        txbuf[4]  = ((va&0x3F)<<2)|((vb>>15)&0x3);
        txbuf[5]  = (vb>>7) & 0xFF;
        txbuf[6]  = ((vb&0x7F)<<1) | ((vc>>16)&0x1);
        txbuf[7]  = (vc>>8) & 0xFF;
        txbuf[8]  = vc & 0xFF;
        txbuf[9]  = utc>>24;             /* U3U2...U0 */
        txbuf[10] = utc>>16;             
        txbuf[11] = utc>>8;              
        txbuf[12] = utc& 0xFF;  
        txbuf[13] = len>>8;              /* TH */
        txbuf[14] = len & 0xFF;          /* TL */
        txbuf[15] = 0xFF;                /* CRC */;
        
        // flash_memory_put( FMC_ID_RUNNING, txbuf, 16);
		flash_temp_queue_put( FMC_ID_RUNNING, txbuf, 16);
        
        osal_start_timerEx( task_id, TASK_STORE_UPLOAD_RUNNING_EVT, 800);
		
		return ( events ^ TASK_STORE_SAVE_RUNNING_EVT );
	}
	
	if ( events & TASK_STORE_SAVE_SWIMMING_EVT )
	{
        // 运动数据-游泳      
        // 保存格式 0xEN SS D6 D5 D4 D3 D2 D1 D0 U3 U2 U1 U0 TH TL CRC
        
        memset( txbuf, 0x00, sizeof(txbuf) );
        
        utc = getUTC();
        unsigned long len = (utc - config.train_swimming_utc)/60;
        utc = config.train_swimming_utc;
        unsigned long va = pedometer.counter - config.train_swimming_pedometer;
        unsigned long vb = (int)((pedometer.calorie - config.train_swimming_calorie)*2.15f);
        unsigned long vc = pedometer.distance - config.train_swimming_distance;
        
        if ( vb == 0 )
        {
           return ( events ^ TASK_STORE_SAVE_SWIMMING_EVT );
        }
      
        txbuf[0]  = (0x2<<4) | 0; // EN[7:4]--> 2 游泳
        txbuf[1]  = 0x0 | (0x1<<3);    // SS[3] --> 1 卡路里有效
        txbuf[2]  = (va>>14) & 0x7;     /* D6D5...D0 */
        txbuf[3]  = (va>>6) & 0xFF;
        txbuf[4]  = ((va&0x3F)<<2)|((vb>>15)&0x3);
        txbuf[5]  = (vb>>7) & 0xFF;
        txbuf[6]  = ((vb&0x7F)<<1) | ((vc>>16)&0x1);
        txbuf[7]  = (vc>>8) & 0xFF;
        txbuf[8]  = vc & 0xFF;
        txbuf[9]  = utc>>24;             /* U3U2...U0 */
        txbuf[10] = utc>>16;             
        txbuf[11] = utc>>8;              
        txbuf[12] = utc & 0xFF;  
        txbuf[13] = len>>8;              /* TH */
        txbuf[14] = len & 0xFF;          /* TL */
        txbuf[15] = 0xFF;                /* CRC */;
        
        // flash_memory_put( FMC_ID_RUNNING, txbuf, 16); 
		flash_temp_queue_put( FMC_ID_RUNNING, txbuf, 16); 
        
        osal_start_timerEx( task_id, TASK_STORE_UPLOAD_RUNNING_EVT, 800);
		
		return ( events ^ TASK_STORE_SAVE_SWIMMING_EVT );
	}
	
	return 0;
}

void taskStoreInit( unsigned long task_id )
{
	taskStoreTaskId = task_id;
}
