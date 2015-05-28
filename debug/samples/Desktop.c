/**
 * @file
 *
 * @author Dalian University of Technology
 *
 * @section LICENSE
 *
 * Copyright (C) 2010 Dalian University of Technology
 *
 * This file is part of EDUGUI.
 *
 * EDUGUI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * EDUGUI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EDUGUI; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 * All rights reserved.
**/

# include <stdio.h>
# include <sys/types.h>
# include <string.h>
# include <unistd.h>

# include "geometry.h"
# include "comm.h"
# include "application.h"
# include "client_lib.h"
# include "widget.h"

#define APP_NUMBER 6

 struct color light_green = {0xcc, 0xff, 0x99, 0};
 struct color barely_blue = {0xcb, 0xf3, 0xfb, 0};
 struct color xue_blue = {0x77,0x7b,0xce,0};
 struct color heavy_blue = {0x2e,0x22,0xff,0};
 struct color friut_green = {0x8a,0xce,0x57,0};
 struct color light_red = {0xd1,0x75,0x47,0};

void sin_app(){
	pid_t id;
	id = fork();
	if(id == 0){
		execl("/home/wangfei/egui/_bulid/debug/samples/single_window","./single_window",NULL);
	}
}
void pop_app(){
	pid_t id;
	id = fork();
	if(id == 0){
		execl("/home/wangfei/egui/_bulid/debug/samples/pop_up_window","./pop_up_window",NULL);
	}
}
void calc_app(){
	pid_t id;
	id = fork();
	if(id == 0){
		execl("/home/wangfei/egui/_bulid/debug/samples/calculator/calculator","./calculator",NULL);
	}
}
void game_app(){
	pid_t id;
	id = fork();
	if(id == 0){
		execl("/home/wangfei/egui/_bulid/debug/samples/game","./game",NULL);
	}
}
void file_app(){
	pid_t id;
	id = fork();
	if(id == 0){
		execl("/home/wangfei/egui/_bulid/debug/samples/file_browser/file_browser","./file_browser",NULL);
	}
}

void end_app(){
	pid_t id;
	id = fork();
	if(id == 0){
		execl("/home/wangfei/egui/_bulid/debug/samples/shutdown","./shutdown",NULL);
	}
}

si_t icon_calc_callback(void * ic, void * msg)
{

         struct icon * i=ic;
	 union message * m = msg;
	 switch(m->base.type)
	 {
		 case MESSAGE_TYPE_MOUSE_SINGLE_CLICK:
              calc_app();
			  break;
		default:
			  icon_default_callback(ic,msg);
			  break;
	 }
  return 0;

}

si_t icon_file_callback(void * ic, void * msg)
{

         struct icon * i=ic;
	 union message * m = msg;
	 switch(m->base.type)
	 {
		 case MESSAGE_TYPE_MOUSE_SINGLE_CLICK:
              file_app();
			  break;
		default:
			  icon_default_callback(ic,msg);
			  break;
	 }
  return 0;

}

si_t icon_game_callback(void * ic, void * msg)
{

         struct icon * i=ic;
	 union message * m = msg;
	 switch(m->base.type)
	 {
		 case MESSAGE_TYPE_MOUSE_SINGLE_CLICK:
              game_app();
			  break;
		default:
			  icon_default_callback(ic,msg);
			  break;
	 }
  return 0;

}

si_t icon_sin_callback(void * ic, void * msg)
{

         struct icon * i=ic;
	 union message * m = msg;
	 switch(m->base.type)
	 {
		 case MESSAGE_TYPE_MOUSE_SINGLE_CLICK:
              sin_app();
			  break;
		default:
			  icon_default_callback(ic,msg);
			  break;
	 }
  return 0;

}

si_t icon_pop_callback(void * ic, void * msg)
{

         struct icon * i=ic;
	 union message * m = msg;
	 switch(m->base.type)
	 {
		 case MESSAGE_TYPE_MOUSE_SINGLE_CLICK:
              pop_app();
			  break;
		default:
			  icon_default_callback(ic,msg);
			  break;
	 }
  return 0;

}

si_t icon_end_callback(void * ic, void * msg)
{

         struct icon * i=ic;
	 union message * m = msg;
	 switch(m->base.type)
	 {
		 case MESSAGE_TYPE_MOUSE_SINGLE_CLICK:
              end_app();
			  break;
		default:
			  icon_default_callback(ic,msg);
			  break;
	 }
  return 0;

}

/*
    测试 button
*/
int main()
{
    si_t video_access_mode = VIDEO_ACCESS_MODE_BUFFER;
	si_t app_type = APPLICATION_TYPE_DESKTOP;
	si_t screen_w = 0, screen_h = 0;
    struct window * w = NULL;
	struct image_view * im;
	struct icon*  ic[APP_NUMBER];
	int i=0;

    /* 初始化用户应用程序 */
    application_init(video_access_mode, app_type, "desktop");
    /* 申请窗口 */
    w = desktop_init("desktop	");
    /* 申请失败 */
    if(w == NULL)
    {
        application_exit(); 
        return -1;
    }
    screen_w = get_screen_size_w();
    screen_h = get_screen_size_h();
	desktop_set_bounds(w, 0, 0, screen_w, screen_h);
	desktop_set_color(w, NULL, &xue_blue);



	/* 画背景图片 */
   im = image_view_init("/home/wangfei/egui/resource/icons/desktop/desktop.bmp");
   if(im == NULL)
    {
        application_exit();
        return -1;
    }
	if(NULL == im)
	{
		application_exit();
		return -1;
	}
	image_view_set_bounds(im, 0, 30, screen_w ,screen_h+30);



	for(i=0;i<APP_NUMBER;i++){
		/* 申请按钮 */
    	ic[i] = icon_init(2);
    	/* 申请失败 */
    	if(ic[i] == NULL)
    	{
        	application_exit();
        	return -1;
    	}
    	ic[i]->back_color.r = 0;
    	ic[i]->back_color.g = 100;
    	ic[i]->back_color.b = 0;
    	ic[i]->back_color.a = 0;
    	icon_set_bounds(ic[i] ,30,(i+1)*100,48,48);
    	icon_set_is_text_visiable(ic[i] ,0);
    }
    /* 第一个是计算器 */
	icon_set_text(ic[0],"calc");
	icon_set_img_path(ic[0],"/home/wangfei/egui/resource/icons/calculator_big.bmp");
	ic[0]->callback = icon_calc_callback;

	/* 第二个是资源管理器 */
	icon_set_text(ic[1],"file");
	icon_set_img_path(ic[1],"/home/wangfei/egui/resource/icons/file_browser_big.bmp");
	ic[1]->callback = icon_file_callback;	
    
    /* 第三个是game */
	icon_set_text(ic[2],"game");
	icon_set_img_path(ic[2],"/home/wangfei/egui/resource/icons/editerbasic_big.bmp");
	ic[2]->callback = icon_game_callback;    
    
    /* 第四个是single */
	icon_set_text(ic[3],"sin");
	icon_set_img_path(ic[3],"/home/wangfei/egui/resource/icons/single_window_big.bmp");
	ic[3]->callback = icon_sin_callback;  
	  
    /* 第五个是pop */
	icon_set_text(ic[4],"pop");
	icon_set_img_path(ic[4],"/home/wangfei/egui/resource/icons/multi_windows_big.bmp");
	ic[4]->callback = icon_pop_callback;

	/* 第六个是 end */
	icon_set_text(ic[5],"end");
	icon_set_img_path(ic[5],"/home/wangfei/egui/resource/icons/toplevel_child_big.bmp");
	ic[5]->callback = icon_end_callback;	






    /* 背景图片添加到窗口 */
    object_attach_child(OBJECT_POINTER(w), OBJECT_POINTER(im));
    
    /* 将icon添加到窗口 */
    for(i=0;i<APP_NUMBER;i++)
    	object_attach_child(OBJECT_POINTER(im), OBJECT_POINTER(ic[i]));
   
    /* 添加顶层窗口 */
    application_add_window(NULL, w);
    /* 设置主窗口 */
    application_set_main_window(w);
    /* 运行 */
    application_exec();

    return 0;
}
