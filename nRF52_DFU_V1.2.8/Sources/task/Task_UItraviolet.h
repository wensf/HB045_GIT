#ifndef __TASK_UITRAVIOLET_H__
#define __TASK_UITRAVIOLET_H__

#define TASK_UITRAVIOLET_START_EVT		    0x00000001
#define TASK_UITRAVIOLET_STOP_EVT           0x00000002
#define TASK_UITRAVIOLET_INIT_EVET          0x00000004
#define TASK_UIT_UPDATE_UV_EVT              0x00000008
#define TASK_UIT_SAVE_UIT_EVT               0x00000010
#define TASK_UIT_REPORT_UIT_EVT             0x00000020

extern short UIT_adc;
extern float UIT_vol;
extern float UIT_cm2;
extern float UIT_i; 
extern float UIT_cm2_save[2];
extern float UIT_i_save[2]; 
extern unsigned char uit_notify_enable;
extern unsigned char uit_warnning_enable;
extern unsigned char uit_warnning_val;
extern unsigned char uit_warnning_interval;

extern unsigned long taskUItravioletTaskId;

extern unsigned long taskUItraviolet( unsigned long task_id, unsigned long events );
extern void taskUItravioletInit( unsigned long task_id );

#endif
