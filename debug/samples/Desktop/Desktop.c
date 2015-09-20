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
#include <time.h>

# include "geometry.h"
# include "comm.h"
# include "application.h"
# include "client_lib.h"
# include "widget.h"

# include "desktop.h"
# include "taskbar.h"
#define APP_NUMBER 6




struct window * Desktop_w = NULL;
struct image_view * Desktop_im;
struct desktop_info desktop;
struct icon** ic_desktop_ptr;
struct timeval* last_do_time;
/* 初始化任务栏状态 */
si_t bar_num=0;



si_t diff_timeval(struct timeval * t1, struct timeval * t2, struct timeval * result)
{
    if(t1->tv_usec < t2->tv_usec)
    {
        result->tv_usec = t1->tv_usec + 1000000 - t2->tv_usec;
        result->tv_sec = t1->tv_sec - 1 - t2->tv_sec;
    }
    else
    {
        result->tv_usec = t1->tv_usec - t2->tv_usec;
        result->tv_sec = t1->tv_sec - t2->tv_sec;
    }

    return 0;
}



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
	struct icon * ic_ptr=ic;
	union message * m = msg;
	switch(m->base.type)
	{
		case MESSAGE_TYPE_MOUSE_PRESS:
			last_do_time[0]=m->base.time;			  
			break;

		case MESSAGE_TYPE_MOUSE_RELEASE:
		{
			struct timeval default_time = {0};
			last_do_time[0]=default_time;	
			 
		}
			break;
		case MESSAGE_TYPE_MOUSE_SINGLE_CLICK:
		{
			if(ic_ptr->flag==0){
				for(int i=0;i<APP_NUMBER;i++){
					icon_set_img_path(ic_desktop_ptr[i], ic_desktop_ptr[i]->img_normal_path);
					ic_desktop_ptr[i]->flag=0;
				}
				icon_set_img_path(ic_ptr, ic_ptr->img_select_path);
				ic_ptr->flag=1;
			}
			else{
				icon_set_img_path(ic_ptr, ic_ptr->img_normal_path);
				ic_ptr->flag=0;
			}

			struct timeval default_time = {0};
			last_do_time[0]=default_time;
			/*
			icon_set_bounds(ic,200,200,48,64); ///////
			// 桌面刷新重绘 
			image_view_reshow(Desktop_im);
  			// 所有图标重绘 
			*/
			for(int i=0;i<APP_NUMBER;i++){
			  	icon_repaint(ic_desktop_ptr[i]);
			  	icon_show(ic_desktop_ptr[i]);
			}
			
		}
			break;
	
		case MESSAGE_TYPE_MOUSE_DOUBLE_CLICK:
			icon_set_img_path(ic_ptr, ic_ptr->img_normal_path);
			ic_ptr->flag=0;
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
	struct icon * ic_ptr=ic;
	union message * m = msg;
	switch(m->base.type)
	{
		case MESSAGE_TYPE_MOUSE_PRESS:
			last_do_time[1]=m->base.time;			  
			break;

		case MESSAGE_TYPE_MOUSE_RELEASE:
		{
			struct timeval default_time = {0};
			last_do_time[1]=default_time;	
			 
		}
			break;
		case MESSAGE_TYPE_MOUSE_SINGLE_CLICK:
		{
			if(ic_ptr->flag==0){
				for(int i=0;i<APP_NUMBER;i++){
					icon_set_img_path(ic_desktop_ptr[i], ic_desktop_ptr[i]->img_normal_path);
					ic_desktop_ptr[i]->flag=0;
				}
				icon_set_img_path(ic_ptr, ic_ptr->img_select_path);
				ic_ptr->flag=1;
			}
			else{
				icon_set_img_path(ic_ptr, ic_ptr->img_normal_path);
				ic_ptr->flag=0;
			}

			struct timeval default_time = {0};
			last_do_time[1]=default_time;
			/*
			icon_set_bounds(ic,200,200,48,64); ///////
			// 桌面刷新重绘 
			image_view_reshow(Desktop_im);
  			// 所有图标重绘 
			*/
			for(int i=0;i<APP_NUMBER;i++){
			  	icon_repaint(ic_desktop_ptr[i]);
			  	icon_show(ic_desktop_ptr[i]);
			}
			
		}
			break;
	
		case MESSAGE_TYPE_MOUSE_DOUBLE_CLICK:
			icon_set_img_path(ic_ptr, ic_ptr->img_normal_path);
			ic_ptr->flag=0;
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
	struct icon * ic_ptr=ic;
	union message * m = msg;
	switch(m->base.type)
	{
		case MESSAGE_TYPE_MOUSE_PRESS:
			last_do_time[2]=m->base.time;			  
			break;

		case MESSAGE_TYPE_MOUSE_RELEASE:
		{
			struct timeval default_time = {0};
			last_do_time[2]=default_time;	
			 
		}
			break;
		case MESSAGE_TYPE_MOUSE_SINGLE_CLICK:
		{
			if(ic_ptr->flag==0){
				for(int i=0;i<APP_NUMBER;i++){
					icon_set_img_path(ic_desktop_ptr[i], ic_desktop_ptr[i]->img_normal_path);
					ic_desktop_ptr[i]->flag=0;
				}
				icon_set_img_path(ic_ptr, ic_ptr->img_select_path);
				ic_ptr->flag=1;
			}
			else{
				icon_set_img_path(ic_ptr, ic_ptr->img_normal_path);
				ic_ptr->flag=0;
			}

			struct timeval default_time = {0};
			last_do_time[2]=default_time;
			/*
			icon_set_bounds(ic,200,200,48,64); ///////
			// 桌面刷新重绘 
			image_view_reshow(Desktop_im);
  			// 所有图标重绘 
			*/
			for(int i=0;i<APP_NUMBER;i++){
			  	icon_repaint(ic_desktop_ptr[i]);
			  	icon_show(ic_desktop_ptr[i]);
			}
			
		}
			break;
	
		case MESSAGE_TYPE_MOUSE_DOUBLE_CLICK:
			icon_set_img_path(ic_ptr, ic_ptr->img_normal_path);
			ic_ptr->flag=0;
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
	struct icon * ic_ptr=ic;
	union message * m = msg;
	switch(m->base.type)
	{
		case MESSAGE_TYPE_MOUSE_PRESS:
			last_do_time[3]=m->base.time;			  
			break;

		case MESSAGE_TYPE_MOUSE_RELEASE:
		{
			struct timeval default_time = {0};
			last_do_time[3]=default_time;	
			 
		}
			break;
		case MESSAGE_TYPE_MOUSE_SINGLE_CLICK:
		{
			if(ic_ptr->flag==0){
				for(int i=0;i<APP_NUMBER;i++){
					icon_set_img_path(ic_desktop_ptr[i], ic_desktop_ptr[i]->img_normal_path);
					ic_desktop_ptr[i]->flag=0;
				}
				icon_set_img_path(ic_ptr, ic_ptr->img_select_path);
				ic_ptr->flag=1;
			}
			else{
				icon_set_img_path(ic_ptr, ic_ptr->img_normal_path);
				ic_ptr->flag=0;
			}

			struct timeval default_time = {0};
			last_do_time[3]=default_time;
			/*
			icon_set_bounds(ic,200,200,48,64); ///////
			// 桌面刷新重绘 
			image_view_reshow(Desktop_im);
  			// 所有图标重绘 
			*/
			for(int i=0;i<APP_NUMBER;i++){
			  	icon_repaint(ic_desktop_ptr[i]);
			  	icon_show(ic_desktop_ptr[i]);
			}
			
		}
			break;
	
		case MESSAGE_TYPE_MOUSE_DOUBLE_CLICK:
			icon_set_img_path(ic_ptr, ic_ptr->img_normal_path);
			ic_ptr->flag=0;
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
	struct icon * ic_ptr=ic;
	union message * m = msg;
	switch(m->base.type)
	{
		case MESSAGE_TYPE_MOUSE_PRESS:
			last_do_time[4]=m->base.time;			  
			break;

		case MESSAGE_TYPE_MOUSE_RELEASE:
		{
			struct timeval default_time = {0};
			last_do_time[4]=default_time;	
			 
		}
			break;
		case MESSAGE_TYPE_MOUSE_SINGLE_CLICK:
		{
			if(ic_ptr->flag==0){
				for(int i=0;i<APP_NUMBER;i++){
					icon_set_img_path(ic_desktop_ptr[i], ic_desktop_ptr[i]->img_normal_path);
					ic_desktop_ptr[i]->flag=0;
				}
				icon_set_img_path(ic_ptr, ic_ptr->img_select_path);
				ic_ptr->flag=1;
			}
			else{
				icon_set_img_path(ic_ptr, ic_ptr->img_normal_path);
				ic_ptr->flag=0;
			}

			struct timeval default_time = {0};
			last_do_time[4]=default_time;
			/*
			icon_set_bounds(ic,200,200,48,64); ///////
			// 桌面刷新重绘 
			image_view_reshow(Desktop_im);
  			// 所有图标重绘 
			*/
			for(int i=0;i<APP_NUMBER;i++){
			  	icon_repaint(ic_desktop_ptr[i]);
			  	icon_show(ic_desktop_ptr[i]);
			}
			
		}
			break;
	
		case MESSAGE_TYPE_MOUSE_DOUBLE_CLICK:
			icon_set_img_path(ic_ptr, ic_ptr->img_normal_path);
			ic_ptr->flag=0;
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
	struct icon * ic_ptr=ic;
	union message * m = msg;
	switch(m->base.type)
	{
		case MESSAGE_TYPE_MOUSE_PRESS:
			last_do_time[5]=m->base.time;			  
			break;

		case MESSAGE_TYPE_MOUSE_RELEASE:
		{
			struct timeval default_time = {0};
			last_do_time[5]=default_time;	
			 
		}
			break;
		case MESSAGE_TYPE_MOUSE_SINGLE_CLICK:
		{
			if(ic_ptr->flag==0){
				for(int i=0;i<APP_NUMBER;i++){
					icon_set_img_path(ic_desktop_ptr[i], ic_desktop_ptr[i]->img_normal_path);
					ic_desktop_ptr[i]->flag=0;
				}
				icon_set_img_path(ic_ptr, ic_ptr->img_select_path);
				ic_ptr->flag=1;
			}
			else{
				icon_set_img_path(ic_ptr, ic_ptr->img_normal_path);
				ic_ptr->flag=0;
			}

			struct timeval default_time = {0};
			last_do_time[5]=default_time;
			/*
			icon_set_bounds(ic,200,200,48,64); ///////
			// 桌面刷新重绘 
			image_view_reshow(Desktop_im);
  			// 所有图标重绘 
			*/
			for(int i=0;i<APP_NUMBER;i++){
			  	icon_repaint(ic_desktop_ptr[i]);
			  	icon_show(ic_desktop_ptr[i]);
			}
			
		}
			break;
	
		case MESSAGE_TYPE_MOUSE_DOUBLE_CLICK:
			icon_set_img_path(ic_ptr, ic_ptr->img_normal_path);
			ic_ptr->flag=0;
			end_app();
			break;
		default:
			icon_default_callback(ic,msg);
			break;
	}
	return 0;
}


/* 桌面的处理函数 */
void desktop_handler(addr_t arg, union message* msg)
{
	struct desktop_info* desktop_info_ptr = (struct desktop_info*)arg;
	si_t window_descripter = message_get_window_descriptor(msg);	
	/* 初始化 */
	static flag = 0;
	if(flag == 0){
		desktop_info_init(desktop_info_ptr);
		flag = 1;
	}
		
	switch(message_get_type(msg))
	{
		/* 处理桌面图标拖动的情况 */
		case MESSAGE_TYPE_MOUSE_RELEASE:
		 {	
				int find_num=0;  //查找正在作用的桌面图标
				for(find_num=0; find_num < APP_NUMBER; find_num++){
					if(last_do_time[find_num].tv_sec != 0 || last_do_time[find_num].tv_usec != 0)
						break;
				}
				/* 找到正在起作用的桌面图标，执行拖动处理 */
				if(find_num < APP_NUMBER) {			
					struct timeval difference = {0};
					diff_timeval(&(msg->base.time), &last_do_time[find_num], &difference);
					if(difference.tv_sec == 0 && difference.tv_usec < 300000){	//按下时间超过0.3秒认为拖动
						struct timeval default_time = {0};
						last_do_time[find_num]=default_time;
					}
					else{
			  				struct point new_point = msg->base.cursor_position;
              				//icon_set_bounds(ic_desktop_ptr[0],200,200,48,64);
			 				icon_set_bounds(ic_desktop_ptr[find_num],new_point.x, new_point.y, 48, 64);
			  				/* 桌面刷新重绘 */
			  				image_view_reshow(Desktop_im);
  			  				/* 所有图标重绘 */
				
			  				for(int i=0;i<APP_NUMBER;i++){
			  					icon_repaint(ic_desktop_ptr[i]);
			  					icon_show(ic_desktop_ptr[i]);
			  				}
							struct timeval default_time = {0};
							last_do_time[find_num]=default_time;
					}
				}		  
		 }
			break;
		/* 任务栏的激活处理 */
		case MESSAGE_TYPE_MOUSE_SINGLE_CLICK:
		{
			struct point* point_ptr=message_get_cursor_position(msg);
			si_t x=point_ptr->x, y=point_ptr->y;
			if(x>80&& x<(bar_num +1)*80 &&y<30){
				int i=(x-80)/80;
				struct window_info * win_info_ptr = (struct window_info *) vector_at(&(desktop_info_ptr->window_info_vector),i);
				activate_window(win_info_ptr->window_descripter);
			} 

		}
		break;

		/* 有程序启动时记录并添加到任务栏 */
		case MESSAGE_TYPE_WINDOW_REGISTER:
		{
			bar_num++;
			
			struct window_info * win_info_ptr = (struct window_info *)malloc(sizeof(struct window_info));
			char *title= (char*)malloc(20);
			
			strcpy(title,(msg->window_register).title);
			window_info_init(win_info_ptr, title, window_descripter);
			vector_push_back(desktop_info_ptr, win_info_ptr, sizeof(struct window_info));	
			desktop_bar_repaint(global_application.main_window);			
    	}
		break;

		/* 程序推出时从记录中删除并在任务栏关闭 */	
		case MESSAGE_TYPE_APP_WINDOW_CANCEL:
		{
			bar_num--;
			int i = desktop_info_find_window_num(desktop_info_ptr, window_descripter);
			vector_erase(&(desktop_info_ptr->window_info_vector),i);
			desktop_bar_repaint(global_application.main_window);
		}
		break;
	
	}
	
}




/*
    桌面主程序入口
*/
int main()
{
    si_t video_access_mode = VIDEO_ACCESS_MODE_BUFFER;
	si_t app_type = APPLICATION_TYPE_DESKTOP;
	si_t screen_w = 0, screen_h = 0;
	
	int i=0;

	ic_desktop_ptr = (struct icon**) malloc(sizeof(struct icon*)*APP_NUMBER);
	/* 定义各个桌面图标最后作用时间，并初始化 */
	last_do_time = (struct timeval*) malloc(sizeof(struct timeval)*APP_NUMBER);
	for(i=0;i<APP_NUMBER;i++){
		last_do_time[i].tv_sec=0;
		last_do_time[i].tv_usec=0;
	}
	
	

    /* 初始化桌面程序 */
    application_init(video_access_mode, app_type, "desktop");
    application_desktop_set(&desktop, desktop_handler);
    /* 申请桌面主窗口 */
    Desktop_w = desktop_init("EGUI");
    /* 申请失败 */
    if(Desktop_w == NULL)
    {
        application_exit(); 
        return -1;
    }
	/* 根据用户屏幕配置桌面大小 */
    screen_w = get_screen_size_w();
    screen_h = get_screen_size_h();
	desktop_set_bounds(Desktop_w, 0, 0, screen_w, screen_h);
	desktop_set_color(Desktop_w, NULL, &xue_blue);



	/* 画背景图片 */
    Desktop_im = image_view_init("/home/wangfei/egui/resource/icons/desktop/desktop11.bmp");
    if(Desktop_im == NULL)
    {
        application_exit();
        return -1;
    }
	image_view_set_bounds(Desktop_im, 0, 30, screen_w ,screen_h-30);


	/* 对桌面按钮初始化 */
	for(i=0;i<APP_NUMBER;i++){
		/* 申请按钮 */
    	ic_desktop_ptr[i] = icon_init(2);
    	/* 申请失败 */
    	if(ic_desktop_ptr[i] == NULL)
    	{
        	application_exit();
        	return -1;
    	}
    	ic_desktop_ptr[i]->back_color.r = 0;
    	ic_desktop_ptr[i]->back_color.g = 100;
    	ic_desktop_ptr[i]->back_color.b = 0;
    	ic_desktop_ptr[i]->back_color.a = 0;
    	icon_set_bounds(ic_desktop_ptr[i] ,30,(i+1)*70,48,64); //要求所有桌面图标为48*48
    	icon_set_is_text_visiable(ic_desktop_ptr[i] ,1);
    }
	/* 配置各个桌面按钮 */
    /* 第一个是计算器 */
	icon_set_text(ic_desktop_ptr[0],"calc");
	icon_set_img_path(ic_desktop_ptr[0],"/home/wangfei/egui/resource/icons/calculator_big.bmp");
	icon_set_img_normal_path(ic_desktop_ptr[0],"/home/wangfei/egui/resource/icons/calculator_big.bmp");
	icon_set_img_select_path(ic_desktop_ptr[0],"/home/wangfei/egui/resource/icons/calculator_select_big.bmp");
	ic_desktop_ptr[0]->callback = icon_calc_callback;

	/* 第二个是资源管理器 */
	icon_set_text(ic_desktop_ptr[1],"file");
	icon_set_img_path(ic_desktop_ptr[1],"/home/wangfei/egui/resource/icons/file_browser_big.bmp");
	icon_set_img_normal_path(ic_desktop_ptr[1],"/home/wangfei/egui/resource/icons/file_browser_big.bmp");
	icon_set_img_select_path(ic_desktop_ptr[1],"/home/wangfei/egui/resource/icons/file_browser_select_big.bmp");
	ic_desktop_ptr[1]->callback = icon_file_callback;	
    
    /* 第三个是game */
	icon_set_text(ic_desktop_ptr[2],"game");
	icon_set_img_path(ic_desktop_ptr[2],"/home/wangfei/egui/resource/icons/game_big.bmp");
	icon_set_img_normal_path(ic_desktop_ptr[2],"/home/wangfei/egui/resource/icons/game_big.bmp");
	icon_set_img_select_path(ic_desktop_ptr[2],"/home/wangfei/egui/resource/icons/game_select_big.bmp");
	ic_desktop_ptr[2]->callback = icon_game_callback;    
    
    /* 第四个是single */
	icon_set_text(ic_desktop_ptr[3],"sin");
	icon_set_img_path(ic_desktop_ptr[3],"/home/wangfei/egui/resource/icons/single_window_big.bmp");
	icon_set_img_normal_path(ic_desktop_ptr[3],"/home/wangfei/egui/resource/icons/single_window_big.bmp");
	icon_set_img_select_path(ic_desktop_ptr[3],"/home/wangfei/egui/resource/icons/single_window_select_big.bmp");
	ic_desktop_ptr[3]->callback = icon_sin_callback;  
	  
    /* 第五个是pop */
	icon_set_text(ic_desktop_ptr[4],"pop");
	icon_set_img_path(ic_desktop_ptr[4],"/home/wangfei/egui/resource/icons/pop_up_window_big.bmp");
	icon_set_img_normal_path(ic_desktop_ptr[4],"/home/wangfei/egui/resource/icons/pop_up_window_big.bmp");
	icon_set_img_select_path(ic_desktop_ptr[4],"/home/wangfei/egui/resource/icons/pop_up_window_select_big.bmp");
	ic_desktop_ptr[4]->callback = icon_pop_callback;

	/* 第六个是 end */
	icon_set_text(ic_desktop_ptr[5],"end");
	icon_set_img_path(ic_desktop_ptr[5],"/home/wangfei/egui/resource/icons/shutdown_big.bmp");
	icon_set_img_normal_path(ic_desktop_ptr[5],"/home/wangfei/egui/resource/icons/shutdown_big.bmp");
	icon_set_img_select_path(ic_desktop_ptr[5],"/home/wangfei/egui/resource/icons/shutdown_select_big.bmp");
	ic_desktop_ptr[5]->callback = icon_end_callback;	

    /* 背景图片添加到窗口 */
    object_attach_child(OBJECT_POINTER(Desktop_w), OBJECT_POINTER(Desktop_im));   
    /* 将icon添加到窗口 */
    for(i=0;i<APP_NUMBER;i++)
    	object_attach_child(OBJECT_POINTER(Desktop_im), OBJECT_POINTER(ic_desktop_ptr[i]));
   



    /* 添加顶层窗口 */
    application_add_window(NULL, Desktop_w);
    /* 设置主窗口 */
    application_set_main_window(Desktop_w);
    /* 运行 */
    application_exec();

    return 0;
}
