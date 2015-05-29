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


struct window * Desktop_w = NULL;
struct image_view * Desktop_im;


/**
 * struct window_info
 **/
struct window_info
{
	si_t window_descripter;
	char* title;
};

void window_info_init(struct window_info* w, char* title, si_t d)
{
	w->window_descripter = d;
	w->title = title;
}

void window_info_exit(struct window_info* w, addr_t arg)
{
	free(w->title);
}

/**
 * 用于判断是否相等
 **/
si_t window_info_cmp(addr_t w, addr_t window_descripter)
{
	return ((struct window_info*)w)->window_descripter == (si_t)window_descripter;
}



/**
 * struct desktop_info
 **/
struct desktop_info
{
	struct vector window_info_vector;
};

void desktop_info_init(struct desktop_info* d)
{
	vector_init(&d->window_info_vector);
}

void desktop_info_exit(struct desktop_info* d)
{
	vector_for_each(&d->window_info_vector, NULL, window_info_exit);
}

struct window_info* desktop_info_find_window(struct desktop_info* d, si_t window_descripter)
{
	si_t i = vector_find(&d->window_info_vector, window_descripter, window_info_cmp);
	return (struct window_info*)vector_at(&d->window_info_vector, i);
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


si_t
button_activave_callback
(void * btn,
 void * msg)
{
    
	struct button * b = btn;
    switch(message_get_type(msg))
    {
        case MESSAGE_TYPE_MOUSE_SINGLE_CLICK:
            activate_window(b-> custom_data);
            break;

        default:
            button_default_callback(b, msg);
            break;
    }

    return 0;
}


void desktop_handler(addr_t arg, union message* msg)
{
	struct desktop_info* desktop_info_ptr = (struct desktop_info*)arg;
	si_t window_descripter = message_get_window_descriptor(msg);
	static flag = 0;
	if(flag == 0){
		desktop_info_init(desktop_info_ptr);
		flag = 1;
	}
	
	switch(message_get_type(msg))
	{
	case MESSAGE_TYPE_WINDOW_REGISTER:
	{
		struct window_info * win_info_ptr = (struct window_info *)malloc(sizeof(struct window_info));
		window_info_init(win_info_ptr, NULL, window_descripter);
		vector_push_back(desktop_info_ptr, win_info_ptr, sizeof(struct window_info));
		
		
		
		
		
		static i=1;
		struct button * b = NULL;
		b = button_init("Shit!");
		
		b->custom_data = window_descripter;
		
		button_set_bounds(b, 100*i, 0, 70, 30);
		i++;
		struct color xue_blue = {0x77,0x7b,0xce,0};
		button_set_color(b, NULL, &xue_blue);
		b->callback = button_activave_callback;
    	object_attach_child(OBJECT_POINTER(global_application.main_window), OBJECT_POINTER(b));
    }
			break;
	/*		
	case MESSAGE_TYPE_WINDOW_CANCEL:
		EGUI_PRINT_INFO("desktop recv window_cancel msg! window %s", win->title);
			break;
	*/
	
	}
	
}




/*
    测试 button
*/
int main()
{
    si_t video_access_mode = VIDEO_ACCESS_MODE_BUFFER;
	si_t app_type = APPLICATION_TYPE_DESKTOP;
	si_t screen_w = 0, screen_h = 0;
	struct desktop_info desktop;
	/*
    struct window * w = NULL;
	struct image_view * im;
	*/
	struct icon*  ic[APP_NUMBER];
	int i=0;
	

    /* 初始化用户应用程序 */
    application_init(video_access_mode, app_type, "desktop");
    application_desktop_set(&desktop, desktop_handler);
    /* 申请窗口 */
    Desktop_w = desktop_init("desktop");
    /* 申请失败 */
    if(Desktop_w == NULL)
    {
        application_exit(); 
        return -1;
    }
    screen_w = get_screen_size_w();
    screen_h = get_screen_size_h();
	desktop_set_bounds(Desktop_w, 0, 0, screen_w, screen_h);
	desktop_set_color(Desktop_w, NULL, &xue_blue);



	/* 画背景图片 */
   Desktop_im = image_view_init("/home/wangfei/egui/resource/icons/desktop/desktop.bmp");
   if(Desktop_im == NULL)
    {
        application_exit();
        return -1;
    }
	if(NULL == Desktop_im)
	{
		application_exit();
		return -1;
	}
	image_view_set_bounds(Desktop_im, 0, 30, screen_w ,screen_h+30);



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
    //object_attach_child(OBJECT_POINTER(Desktop_w), OBJECT_POINTER(Desktop_im));
    
    /* 将icon添加到窗口 */
    for(i=0;i<APP_NUMBER;i++)
    	object_attach_child(OBJECT_POINTER(Desktop_w), OBJECT_POINTER(ic[i]));
   
    /* 添加顶层窗口 */
    application_add_window(NULL, Desktop_w);
    /* 设置主窗口 */
    application_set_main_window(Desktop_w);
    /* 运行 */
    application_exec();

    return 0;
}
