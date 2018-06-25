
#include "string.h"

#include "OSAL.h"
#include "OSAL_Timer.h"
#include "Window.h"
#include "UI_Draw.h"
#include "LCD_ST7735.h"
#include "UserSetting.h"
#include "btprotocol.h"
#include "Task_GUI.h"

#include "UI_win_camera.h"
#include "UI_camera_icon.h"

unsigned char action = 0;
unsigned char take_photo_action[20] = {0xFC,0x19,0x00,0x81,0x00,0x00,};
unsigned char exit_take_photo[20] =   {0xFC,0x19,0x80,0x00,0x00,0x00,};

void show_camera( int x, int y )
{
	DrawUI_Bitmap( (80-64)/2,(160-64)/2, 64, 64, BMP_camera, COLOR_CAMERA_F, COLOR_CAMERA_B);
}

unsigned long win_camera_proc(unsigned long wid, unsigned long msg_type, 
                            unsigned long msg_param, unsigned long *p)
{
	if ( msg_type & WINDOW_CREATE )
	{
		win_ticks = 0;

		if ( config.lcdEnable == 0 )
		{
			lcd_display(1);
		}		

		osal_set_event( taskGUITaskId, TASK_GUI_UPDATE_EVT );
		
		return ( msg_type ^ WINDOW_CREATE );
	}
	
	if ( msg_type & WINDOW_UPDATE )
	{
		win_ticks++;
		
		if ( win_ticks > 60 )
		{
			lcd_display(0);
			
			return ( msg_type ^ WINDOW_UPDATE );
		}

		memset( frame_buffer, 0, sizeof(frame_buffer));
		show_camera( 28, 20 );
		sync_frame();
		
		osal_start_timerEx( taskGUITaskId, TASK_GUI_UPDATE_EVT, 500);
		
		return ( msg_type ^ WINDOW_UPDATE );
	}
	
	if ( msg_type & WINDOW_TOUCH )
	{		
		if ( config.lcdEnable == 0 )
		{
			lcd_display(1);			
			win_ticks = 0;
			msg_type |= WINDOW_UPDATE;
		}else{
			// Todo : 拍照	
			
			bt_protocol_tx( take_photo_action, sizeof(take_photo_action) );
		}
		
		return ( msg_type ^ WINDOW_TOUCH );
	}
	
	if ( msg_type & WINDOW_PRESS )
	{				
		if ( config.lcdEnable == 0 )
		{
			lcd_display(1);			
			win_ticks = 0;
			msg_type |= WINDOW_UPDATE;
		}else{
			// Todo : 退出
			
			bt_protocol_tx( exit_take_photo, sizeof(exit_take_photo) );
						
			msg_type |= WINDOW_DISTORY;
		}		
		
		return ( msg_type ^ WINDOW_PRESS );
	}
	
	if ( msg_type & WINDOW_NOTIFY )
	{   
        /* 当前窗体入栈 */
        window_push( win_current );
        
        /* 通知界面作为当前界面 */
        win_current = NOTIFY_WIN_ID_GET();
        
        /* 调用窗体回调函数以便创建窗体  */
        window[win_current].wproc( win_current, WINDOW_CREATE, 0, 0);
		
		return ( msg_type ^ WINDOW_NOTIFY );
	}	
	
	if ( msg_type & WINDOW_DISTORY )
	{
		window_pop(&win_current);
		
		return window[win_current].wproc( win_current, WINDOW_CREATE, 0, 0 );
	}	
	
	return 0;
}
