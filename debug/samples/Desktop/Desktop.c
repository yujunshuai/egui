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
 * it under the terms of the GNU General Publsh Lshense as published by
 * the Free Software Foundation, either version 2 of the Lshense, or
 * (at your option) any later version.
 *
 * EDUGUI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Publsh Lshense for more details.
 *
 * You should have received a copy of the GNU General Publsh Lshense
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
struct vector sh_desktop_vector;
struct rectangle** area_pptr = NULL;
int** flag_pptr = NULL;
char file_path[]="/home/wangfei/egui/_bulid/debug/samples/";
/* 初始化任务栏状态 */
si_t bar_num=0;
/* 初始化屏幕大小 */
si_t screen_w = 0;
si_t screen_h = 0;

si_t area_num_x=0;
si_t area_num_y=0;
//找到但当前区域已有快捷方式，返回0；
//找到且当前区域无快捷方式，返回1；
//找不到返回-1；
int find_witch_area(struct point p, struct point* area_num){
	for(int i=0;i<area_num_x;i++)
		for(int j=0;j<area_num_y;j++)
			if(p.x>= area_pptr[i][j].x && p.x<= area_pptr[i][j].x+area_pptr[i][j].width && p.y>= area_pptr[i][j].y && p.y<= area_pptr[i][j].y+area_pptr[i][j].height){
				area_num->x=i, area_num->y=j;
				if(flag_pptr[i][j])
					return 0;
				return 1;
			}
	return -1;
}

int reset_shortcut_bound(struct shortcut* sh, struct point area_num){
	if(flag_pptr[area_num.x][area_num.y])
		return -1;	
	int x=area_pptr[area_num.x][area_num.y].x + 13;
	int y=area_pptr[area_num.x][area_num.y].y + 5;
	int width= 54;
	int height= 70;
	shortcut_set_bounds(sh, x, y, width, height);
	flag_pptr[sh->position_x][sh->position_y] = 0;
	flag_pptr[area_num.x][area_num.y] = 1;
	sh->position_x = area_num.x;
	sh->position_y = area_num.y;
	
	return 1;
}

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
	char* full_path=(char*)malloc(strlen(file_path)+13+1);
	strcpy(full_path,file_path);
	strcat(full_path,&"single_window");
	if(id == 0){
		//execl("/home/wangfei/egui/_bulid/debug/samples/single_window","./single_window",NULL);
		execl(*full_path,"./single_window",NULL);
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

si_t shortcut_calc_callback(void * sh, void * msg)
{
	struct shortcut * sh_ptr=sh;
	union message * m = msg;
	switch(m->base.type)
	{
		case MESSAGE_TYPE_MOUSE_PRESS:
			sh_ptr->last_do_time=m->base.time;			  
			break;

		case MESSAGE_TYPE_MOUSE_RELEASE:
		{
			sh_ptr->last_do_time.tv_sec=0;	
			sh_ptr->last_do_time.tv_usec=0;
			 
		}
			break;
		case MESSAGE_TYPE_MOUSE_SINGLE_CLICK:
		{
			if(sh_ptr->flag==0){
				for(int i=0;i<APP_NUMBER;i++){
					struct shortcut* sh = vector_at(&sh_desktop_vector, i);
					shortcut_set_img_path(sh, sh->img_normal_path);
					sh->flag=0;
				}
				shortcut_set_img_path(sh_ptr, sh_ptr->img_select_path);
				sh_ptr->flag=1;
			}
			else{
				shortcut_set_img_path(sh_ptr, sh_ptr->img_normal_path);
				sh_ptr->flag=0;
			}

			sh_ptr->last_do_time.tv_sec=0;	
			sh_ptr->last_do_time.tv_usec=0;
			// 重绘所有桌面快捷方式
			for(int i=0;i<APP_NUMBER;i++){
				struct shortcut* sh = vector_at(&sh_desktop_vector, i);
			  	shortcut_repaint(sh);
			  	shortcut_show(sh);
			}
			
		}
			break;
	
		case MESSAGE_TYPE_MOUSE_DOUBLE_CLICK:
			shortcut_set_img_path(sh_ptr, sh_ptr->img_normal_path);
			sh_ptr->flag=0;
			calc_app();
			break;
		default:
			shortcut_default_callback(sh,msg);
			break;
	}
	return 0;
}

si_t shortcut_file_callback(void * sh, void * msg)
{
	struct shortcut * sh_ptr=sh;
	union message * m = msg;
	switch(m->base.type)
	{
		case MESSAGE_TYPE_MOUSE_PRESS:
			sh_ptr->last_do_time=m->base.time;			  
			break;

		case MESSAGE_TYPE_MOUSE_RELEASE:
		{
			sh_ptr->last_do_time.tv_sec=0;	
			sh_ptr->last_do_time.tv_usec=0;
			 
		}
			break;
		case MESSAGE_TYPE_MOUSE_SINGLE_CLICK:
		{
			if(sh_ptr->flag==0){
				for(int i=0;i<APP_NUMBER;i++){
					struct shortcut* sh = vector_at(&sh_desktop_vector, i);
					shortcut_set_img_path(sh, sh->img_normal_path);
					sh->flag=0;
				}
				shortcut_set_img_path(sh_ptr, sh_ptr->img_select_path);
				sh_ptr->flag=1;
			}
			else{
				shortcut_set_img_path(sh_ptr, sh_ptr->img_normal_path);
				sh_ptr->flag=0;
			}

			sh_ptr->last_do_time.tv_sec=0;	
			sh_ptr->last_do_time.tv_usec=0;
			// 重绘所有桌面快捷方式
			for(int i=0;i<APP_NUMBER;i++){
				struct shortcut* sh = vector_at(&sh_desktop_vector, i);
			  	shortcut_repaint(sh);
			  	shortcut_show(sh);
			}
			
		}
			break;
	
		case MESSAGE_TYPE_MOUSE_DOUBLE_CLICK:
			shortcut_set_img_path(sh_ptr, sh_ptr->img_normal_path);
			sh_ptr->flag=0;
			file_app();
			break;
		default:
			shortcut_default_callback(sh,msg);
			break;
	}
	return 0;
}

si_t shortcut_game_callback(void * sh, void * msg)
{
	struct shortcut * sh_ptr=sh;
	union message * m = msg;
	switch(m->base.type)
	{
		case MESSAGE_TYPE_MOUSE_PRESS:
			sh_ptr->last_do_time=m->base.time;			  
			break;

		case MESSAGE_TYPE_MOUSE_RELEASE:
		{
			sh_ptr->last_do_time.tv_sec=0;	
			sh_ptr->last_do_time.tv_usec=0;
			 
		}
			break;
		case MESSAGE_TYPE_MOUSE_SINGLE_CLICK:
		{
			if(sh_ptr->flag==0){
				for(int i=0;i<APP_NUMBER;i++){
					struct shortcut* sh = vector_at(&sh_desktop_vector, i);
					shortcut_set_img_path(sh, sh->img_normal_path);
					sh->flag=0;
				}
				shortcut_set_img_path(sh_ptr, sh_ptr->img_select_path);
				sh_ptr->flag=1;
			}
			else{
				shortcut_set_img_path(sh_ptr, sh_ptr->img_normal_path);
				sh_ptr->flag=0;
			}

			sh_ptr->last_do_time.tv_sec=0;	
			sh_ptr->last_do_time.tv_usec=0;
			// 重绘所有桌面快捷方式
			for(int i=0;i<APP_NUMBER;i++){
				struct shortcut* sh = vector_at(&sh_desktop_vector, i);
			  	shortcut_repaint(sh);
			  	shortcut_show(sh);
			}
			
		}
			break;
	
		case MESSAGE_TYPE_MOUSE_DOUBLE_CLICK:
			shortcut_set_img_path(sh_ptr, sh_ptr->img_normal_path);
			sh_ptr->flag=0;
			game_app();
			break;
		default:
			shortcut_default_callback(sh,msg);
			break;
	}
	return 0;
}

si_t shortcut_sin_callback(void * sh, void * msg)
{
	struct shortcut * sh_ptr=sh;
	union message * m = msg;
	switch(m->base.type)
	{
		case MESSAGE_TYPE_MOUSE_PRESS:
			sh_ptr->last_do_time=m->base.time;			  
			break;

		case MESSAGE_TYPE_MOUSE_RELEASE:
		{
			sh_ptr->last_do_time.tv_sec=0;	
			sh_ptr->last_do_time.tv_usec=0;
			 
		}
			break;
		case MESSAGE_TYPE_MOUSE_SINGLE_CLICK:
		{
			if(sh_ptr->flag==0){
				for(int i=0;i<APP_NUMBER;i++){
					struct shortcut* sh = vector_at(&sh_desktop_vector, i);
					shortcut_set_img_path(sh, sh->img_normal_path);
					sh->flag=0;
				}
				shortcut_set_img_path(sh_ptr, sh_ptr->img_select_path);
				sh_ptr->flag=1;
			}
			else{
				shortcut_set_img_path(sh_ptr, sh_ptr->img_normal_path);
				sh_ptr->flag=0;
			}

			sh_ptr->last_do_time.tv_sec=0;	
			sh_ptr->last_do_time.tv_usec=0;
			// 重绘所有桌面快捷方式
			for(int i=0;i<APP_NUMBER;i++){
				struct shortcut* sh = vector_at(&sh_desktop_vector, i);
			  	shortcut_repaint(sh);
			  	shortcut_show(sh);
			}
			
		}
			break;
	
		case MESSAGE_TYPE_MOUSE_DOUBLE_CLICK:
			shortcut_set_img_path(sh_ptr, sh_ptr->img_normal_path);
			sh_ptr->flag=0;
			sin_app();
			break;
		default:
			shortcut_default_callback(sh,msg);
			break;
	}
	return 0;
}

si_t shortcut_pop_callback(void * sh, void * msg)
{
	struct shortcut * sh_ptr=sh;
	union message * m = msg;
	switch(m->base.type)
	{
		case MESSAGE_TYPE_MOUSE_PRESS:
			sh_ptr->last_do_time=m->base.time;			  
			break;

		case MESSAGE_TYPE_MOUSE_RELEASE:
		{
			sh_ptr->last_do_time.tv_sec=0;	
			sh_ptr->last_do_time.tv_usec=0;
			 
		}
			break;
		case MESSAGE_TYPE_MOUSE_SINGLE_CLICK:
		{
			if(sh_ptr->flag==0){
				for(int i=0;i<APP_NUMBER;i++){
					struct shortcut* sh = vector_at(&sh_desktop_vector, i);
					shortcut_set_img_path(sh, sh->img_normal_path);
					sh->flag=0;
				}
				shortcut_set_img_path(sh_ptr, sh_ptr->img_select_path);
				sh_ptr->flag=1;
			}
			else{
				shortcut_set_img_path(sh_ptr, sh_ptr->img_normal_path);
				sh_ptr->flag=0;
			}

			sh_ptr->last_do_time.tv_sec=0;	
			sh_ptr->last_do_time.tv_usec=0;
			// 重绘所有桌面快捷方式
			for(int i=0;i<APP_NUMBER;i++){
				struct shortcut* sh = vector_at(&sh_desktop_vector, i);
			  	shortcut_repaint(sh);
			  	shortcut_show(sh);
			}
			
		}
			break;
	
		case MESSAGE_TYPE_MOUSE_DOUBLE_CLICK:
			shortcut_set_img_path(sh_ptr, sh_ptr->img_normal_path);
			sh_ptr->flag=0;
			pop_app();
			break;
		default:
			shortcut_default_callback(sh,msg);
			break;
	}
	return 0;
}

si_t shortcut_end_callback(void * sh, void * msg)
{
	struct shortcut * sh_ptr=sh;
	union message * m = msg;
	switch(m->base.type)
	{
		case MESSAGE_TYPE_MOUSE_PRESS:
			sh_ptr->last_do_time=m->base.time;			  
			break;

		case MESSAGE_TYPE_MOUSE_RELEASE:
		{
			sh_ptr->last_do_time.tv_sec=0;	
			sh_ptr->last_do_time.tv_usec=0;
			 
		}
			break;
		case MESSAGE_TYPE_MOUSE_SINGLE_CLICK:
		{
			if(sh_ptr->flag==0){
				for(int i=0;i<APP_NUMBER;i++){
					struct shortcut* sh = vector_at(&sh_desktop_vector, i);
					shortcut_set_img_path(sh, sh->img_normal_path);
					sh->flag=0;
				}
				shortcut_set_img_path(sh_ptr, sh_ptr->img_select_path);
				sh_ptr->flag=1;
			}
			else{
				shortcut_set_img_path(sh_ptr, sh_ptr->img_normal_path);
				sh_ptr->flag=0;
			}

			sh_ptr->last_do_time.tv_sec=0;	
			sh_ptr->last_do_time.tv_usec=0;
			// 重绘所有桌面快捷方式
			for(int i=0;i<APP_NUMBER;i++){
				struct shortcut* sh = vector_at(&sh_desktop_vector, i);
			  	shortcut_repaint(sh);
			  	shortcut_show(sh);
			}
			
		}
			break;
	
		case MESSAGE_TYPE_MOUSE_DOUBLE_CLICK:
			shortcut_set_img_path(sh_ptr, sh_ptr->img_normal_path);
			sh_ptr->flag=0;
			end_app();
			break;
		default:
			shortcut_default_callback(sh,msg);
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
				struct shortcut* sh_desktop_ptr = NULL;
				int find_num=0;  //查找正在作用的桌面图标
				for(find_num=0; find_num < APP_NUMBER; find_num++){
					sh_desktop_ptr = vector_at(&sh_desktop_vector, find_num);
					if(sh_desktop_ptr->last_do_time.tv_sec != 0 || sh_desktop_ptr->last_do_time.tv_usec != 0)
						break;
				}
				/* 找到正在起作用的桌面图标，执行拖动处理 */
				if(find_num < APP_NUMBER) {			
					struct timeval difference = {0};
					diff_timeval(&(msg->base.time), &(sh_desktop_ptr->last_do_time), &difference);
					if(difference.tv_sec == 0 && difference.tv_usec < 300000){	//按下时间超过0.3秒认为拖动
						sh_desktop_ptr->last_do_time.tv_sec=0;	
						sh_desktop_ptr->last_do_time.tv_usec=0;
					}
					else{
						//设置新位置
			  			struct point new_point = msg->base.cursor_position;
						struct point area_num;
						if( find_witch_area(new_point, &area_num) == 1)
							reset_shortcut_bound(sh_desktop_ptr, area_num);
			 			//shortcut_set_bounds(sh_desktop_ptr, new_point.x, new_point.y, 54, 70);
			  			/* 桌面刷新重绘 */
			  			image_view_reshow(Desktop_im);
  			  			/* 所有图标重绘 */				
			  			for(int i=0;i<APP_NUMBER;i++){
							struct shortcut* sh = vector_at(&sh_desktop_vector, i);
			  				shortcut_repaint(sh);
			  				shortcut_show(sh);
			  			}
						sh_desktop_ptr->last_do_time.tv_sec=0;	
						sh_desktop_ptr->last_do_time.tv_usec=0;
					}
				}		  
		 }
			break;
		/* 任务栏的激活处理 */
		case MESSAGE_TYPE_MOUSE_SINGLE_CLICK:
		{
			struct point* point_ptr=message_get_cursor_position(msg);
			si_t x=point_ptr->x, y=point_ptr->y;
			if(x>80 && x<(bar_num +1)*80 && y<screen_h && y>screen_h-30){
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
	
	int i=0;

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

	area_num_x=screen_w/80;
	area_pptr=(struct rectangle**) malloc(sizeof(struct rectangle*)*area_num_x);
	flag_pptr=(int**) malloc(sizeof(int*)*area_num_x);
	area_num_y=(screen_h - 30)/80;
	for(i=0;i<area_num_x;i++){
		area_pptr[i]=(struct rectangle*) malloc(sizeof(struct rectangle)*area_num_y);
		flag_pptr[i]=(int*) malloc(sizeof(int)*area_num_y);
	}
	for(int j=0;j<area_num_x;j++)
		for(int k=0;k<area_num_y;k++){
			area_pptr[j][k].x=j*80;
			area_pptr[j][k].y=k*80;
			area_pptr[j][k].width=80;
			area_pptr[j][k].height=80;
			flag_pptr[j][k]=0;
	}



	/* 画背景图片 */
    Desktop_im = image_view_init("/home/wangfei/egui/resource/icons/desktop/desktop11.bmp");
    if(Desktop_im == NULL)
    {
        application_exit();
        return -1;
    }
	image_view_set_bounds(Desktop_im, 0, 0, screen_w ,screen_h-30);


	/* 对桌面按钮初始化 */
	for(i=0;i<APP_NUMBER;i++){
		/* 申请按钮 */
    	struct shortcut* sh_desktop_ptr = shortcut_init(2);
    	/* 申请失败 */
    	if(sh_desktop_ptr == NULL)
    	{
        	application_exit();
        	return -1;
    	}
    	sh_desktop_ptr->back_color.r = 0;
    	sh_desktop_ptr->back_color.g = 100;
    	sh_desktop_ptr->back_color.b = 0;
    	sh_desktop_ptr->back_color.a = 0;
    	//shortcut_set_bounds(sh_desktop_ptr ,30,(i+1)*80,54,70); //要求所有桌面图标为54*54
		sh_desktop_ptr->position_x=0;
		sh_desktop_ptr->position_y=i;
		struct point p;
		p.x=sh_desktop_ptr->position_x;
		p.y=sh_desktop_ptr->position_y;
		reset_shortcut_bound(sh_desktop_ptr,p);
		
    	shortcut_set_is_text_visiable(sh_desktop_ptr ,1);
		vector_push_back(&sh_desktop_vector, sh_desktop_ptr, sizeof(struct shortcut));
    }
	/* 配置各个桌面按钮 */
	struct shortcut* sh_desktop_ptr = NULL;
    /* 第一个是计算器 */
	sh_desktop_ptr = vector_at(&sh_desktop_vector, 0);
	shortcut_set_text(sh_desktop_ptr,"calc");
	shortcut_set_img_path(sh_desktop_ptr,"/home/wangfei/egui/resource/icons/calculator_big.bmp");
	shortcut_set_img_normal_path(sh_desktop_ptr,"/home/wangfei/egui/resource/icons/calculator_big.bmp");
	shortcut_set_img_select_path(sh_desktop_ptr,"/home/wangfei/egui/resource/icons/calculator_select_big.bmp");
	sh_desktop_ptr->callback = shortcut_calc_callback;

	/* 第二个是资源管理器 */
	sh_desktop_ptr = vector_at(&sh_desktop_vector, 1);
	shortcut_set_text(sh_desktop_ptr,"file");
	shortcut_set_img_path(sh_desktop_ptr,"/home/wangfei/egui/resource/icons/file_browser_big.bmp");
	shortcut_set_img_normal_path(sh_desktop_ptr,"/home/wangfei/egui/resource/icons/file_browser_big.bmp");
	shortcut_set_img_select_path(sh_desktop_ptr,"/home/wangfei/egui/resource/icons/file_browser_select_big.bmp");
	sh_desktop_ptr->callback = shortcut_file_callback;	
    
    /* 第三个是game */
	sh_desktop_ptr = vector_at(&sh_desktop_vector, 2);
	shortcut_set_text(sh_desktop_ptr,"game");
	shortcut_set_img_path(sh_desktop_ptr,"/home/wangfei/egui/resource/icons/game_big.bmp");
	shortcut_set_img_normal_path(sh_desktop_ptr,"/home/wangfei/egui/resource/icons/game_big.bmp");
	shortcut_set_img_select_path(sh_desktop_ptr,"/home/wangfei/egui/resource/icons/game_select_big.bmp");
	sh_desktop_ptr->callback = shortcut_game_callback;    
    
    /* 第四个是single */
	sh_desktop_ptr = vector_at(&sh_desktop_vector, 3);
	shortcut_set_text(sh_desktop_ptr,"sin");
	shortcut_set_img_path(sh_desktop_ptr,"/home/wangfei/egui/resource/icons/single_window_big.bmp");
	shortcut_set_img_normal_path(sh_desktop_ptr,"/home/wangfei/egui/resource/icons/single_window_big.bmp");
	shortcut_set_img_select_path(sh_desktop_ptr,"/home/wangfei/egui/resource/icons/single_window_select_big.bmp");
	sh_desktop_ptr->callback = shortcut_sin_callback;  
	  
    /* 第五个是pop */
	sh_desktop_ptr = vector_at(&sh_desktop_vector, 4);
	shortcut_set_text(sh_desktop_ptr,"pop");
	shortcut_set_img_path(sh_desktop_ptr,"/home/wangfei/egui/resource/icons/pop_up_window_big.bmp");
	shortcut_set_img_normal_path(sh_desktop_ptr,"/home/wangfei/egui/resource/icons/pop_up_window_big.bmp");
	shortcut_set_img_select_path(sh_desktop_ptr,"/home/wangfei/egui/resource/icons/pop_up_window_select_big.bmp");
	sh_desktop_ptr->callback = shortcut_pop_callback;

	/* 第六个是 end */
	sh_desktop_ptr = vector_at(&sh_desktop_vector, 5);
	shortcut_set_text(sh_desktop_ptr,"end");
	shortcut_set_img_path(sh_desktop_ptr,"/home/wangfei/egui/resource/icons/shutdown_big.bmp");
	shortcut_set_img_normal_path(sh_desktop_ptr,"/home/wangfei/egui/resource/icons/shutdown_big.bmp");
	shortcut_set_img_select_path(sh_desktop_ptr,"/home/wangfei/egui/resource/icons/shutdown_select_big.bmp");
	sh_desktop_ptr->callback = shortcut_end_callback;	

    /* 背景图片添加到窗口 */
    object_attach_child(OBJECT_POINTER(Desktop_w), OBJECT_POINTER(Desktop_im));   
    /* 将shortcut添加到窗口 */
    for(i=0;i<APP_NUMBER;i++){
		sh_desktop_ptr = vector_at(&sh_desktop_vector, i);
    	object_attach_child(OBJECT_POINTER(Desktop_im), OBJECT_POINTER(sh_desktop_ptr));
	}
   



    /* 添加顶层窗口 */
    application_add_window(NULL, Desktop_w);
    /* 设置主窗口 */
    application_set_main_window(Desktop_w);
    /* 运行 */
    application_exec();

    return 0;
}
