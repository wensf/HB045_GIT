#include "OSAL.h"
#include "OSAL_Timer.h"
#include "Task_Motor.h"
#include "Board.h"
#include "UserSetting.h"

void motor_disable(void)
{
	MOTOR_ENABLE(false);
}

unsigned long taskMotorTaskId;

unsigned char viborate_flag = 0;

unsigned long taskMotor( unsigned long task_id, unsigned long events )
{
	if ( events & TASK_MOTOR_BMA_DONE_EVT )
	{	
		if ( viborate_flag == 0 )
		{
			viborate_flag = 1;
			
			MOTOR_ENABLE(true);
			
			osal_start_timerEx( task_id, TASK_MOTOR_BMA_DONE_EVT, 250);
		}else
		{
			viborate_flag = 0;
			MOTOR_ENABLE(false);
		}
		
		return ( events ^ TASK_MOTOR_BMA_DONE_EVT );
	}    
    
    return 0;
}

void taskMotorInit( unsigned long task_id )
{
	taskMotorTaskId = task_id;
	
	MOTOR_INIT();	
}
