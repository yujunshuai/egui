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
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include<time.h>
#include<sys/types.h>
#include<unistd.h>
#include <string.h>

# include "right_click_menu.h"

/* 右键菜单 */
# define MENU_NUM 4

/* 右键菜单 */
static struct button * menu_button[MENU_NUM];
static si_t menu_show = 0;
struct shortcut* sh_desktop_ptr = NULL;
//extern struct image_view * Desktop_im;
/*桌面应用图标数*/
//extern const si_t APP_NUMBER;
//extern struct icon** ic_desktop_ptr;

void create_new_folder(){ 
    si_t i=0;
    byte_t str[100]="/home/wang/egui/_build/MAIN/NEW FOLDER";
    byte_t cpy[100]="/home/wang/egui/_build/MAIN/NEW FOLDER";
    byte_t temp_str[100];
    while(access(str,0)!=-1){//access函数是查看文件是不是存在
    	strcpy(str,cpy);
    	i++;
    	sprintf(temp_str, "%d", i);
    	strcat(str,temp_str);
    }
    if (mkdir(str,0777)) {//如果不存在就用mkdir函数来创建
    	printf("creat folder failed!!!");
    }
}

void create_new_file(){
    si_t i=0;
    byte_t pathname[100] = {"/home/wang/egui/_build/MAIN/NEW FILE"};
    byte_t cpy[100]= {"/home/wang/egui/_build/MAIN/NEW FILE"};
    byte_t temp_str[100];
    
    if(access("MAIN",0)==-1){//access函数是查看文件是不是存在
		if (mkdir("MAIN",0777)) {//如果不存在就用mkdir函数来创建
			printf("creat folder failed!!!");
		}
    }

    while(access(pathname,0)!=-1){//access函数是查看文件是不是存在
		strcpy(pathname,cpy);
		i++;
		sprintf(temp_str, "%d", i);
		strcat(pathname,temp_str);
    }
    
    FILE  *fp;
    if((fp=fopen(pathname,"w"))==NULL)//打开文件 没有就创建
    {
        printf("文件还未创建!\n");
    }

    fprintf(fp,"创建成功");
    fclose(fp);
}

si_t
right_click_menu_NEW_FOLDER
(void * bt,
 void * msg)
{
    switch(message_get_type(msg))
    {
    	case MESSAGE_TYPE_MOUSE_PRESS:
            create_new_folder();
    	    break;

        default:
            button_default_callback(bt, msg);
            break;
    }
    return 0;
}

si_t
right_click_menu_NEW_FILE
(void * bt,
 void * msg)
{
    switch(message_get_type(msg))
    {
    	case MESSAGE_TYPE_MOUSE_PRESS:
            create_new_file();
    	    break;

        default:
            button_default_callback(bt, msg);
            break;
    }
    return 0;
}

si_t
right_click_menu_FLUSH
(void * bt,
 void * msg)
{
    switch(message_get_type(msg))
    {
    	case MESSAGE_TYPE_MOUSE_PRESS:
    	    desktop_flush();
    	    break;

        default:
            button_default_callback(bt, msg);
            break;
    }
    return 0;
}
si_t
right_click_menu_rename
(void * bt,
 void * msg)
{
    switch(message_get_type(msg))
    {
    	case MESSAGE_TYPE_MOUSE_PRESS:
    	    shortcut_set_text(sh_desktop_ptr,"123");
			desktop_flush();
    	    break;

        default:
            button_default_callback(bt, msg);
            break;
    }
    return 0;
}

si_t right_click_menu_init() {
	si_t i = 0;
	for(i=0;i<MENU_NUM;i++)
		menu_button[i]=NULL;
	
	menu_button[0] = button_init("NEW FOLDER");
	/* 申请失败 */
	if(menu_button[0] == NULL)
	{
		application_exit();
		return -1;
	}
	window_set_color(menu_button[0], NULL, &light_green);
    	button_set_bounds(menu_button[0], 0, -30, 0, 0);
	menu_button[0]->callback = right_click_menu_NEW_FOLDER;    
	/* 添加button */   
	object_attach_child(OBJECT_POINTER(Desktop_im), OBJECT_POINTER(menu_button[0]));
	
	menu_button[1] = button_init("NEW FILE");
	/* 申请失败 */
	if(menu_button[1] == NULL)
	{
		application_exit();
		return -1;
	}
	window_set_color(menu_button[1], NULL, &light_green);
    	button_set_bounds(menu_button[1], 0, -30, 0, 0);
	menu_button[1]->callback = right_click_menu_NEW_FILE;    
	/* 添加button */   
	object_attach_child(OBJECT_POINTER(Desktop_im), OBJECT_POINTER(menu_button[1]));
	
	menu_button[2] = button_init("rename");
	/* 申请失败 */
	if(menu_button[2] == NULL)
	{
		application_exit();
		return -1;
	}
	window_set_color(menu_button[2], NULL, &light_green);
    	button_set_bounds(menu_button[2], 0, -30, 0, 0);
	menu_button[2]->callback = right_click_menu_rename;    
	/* 添加button */   
	object_attach_child(OBJECT_POINTER(Desktop_im), OBJECT_POINTER(menu_button[2]));


	menu_button[3] = button_init("FLUSH");
	/* 申请失败 */
	if(menu_button[3] == NULL)
	{
		application_exit();
		return -1;
	}
	window_set_color(menu_button[3], NULL, &light_green);
    	button_set_bounds(menu_button[3], 0, -30, 0, 0);
	menu_button[3]->callback = right_click_menu_FLUSH;    
	/* 添加button */   
	object_attach_child(OBJECT_POINTER(Desktop_im), OBJECT_POINTER(menu_button[3]));
	
	/* 右键菜单不显示 */	
	menu_show = 0;
	
	/*创建桌面文件夹*/
    if(access("/home/wang/egui/_build/MAIN",0)==-1){//access函数是查看文件是不是存在
	if (mkdir("MAIN",0777)) {//如果不存在就用mkdir函数来创建
		printf("creat folder failed!!!");
	}
    }
}

void right_click_menu_handle(union message* msg) {
	//获得目标快捷方式指针
	int find_num=0;  //查找正在作用的桌面图标
	for(find_num=0; find_num < app_number; find_num++){
		sh_desktop_ptr = vector_at(&sh_desktop_vector, find_num);
		if(sh_desktop_ptr->flag==1)
			break;
	}

	si_t i=0;
	if(menu_show == 0){
		struct point* point_ptr=message_get_cursor_position(msg);
		si_t x=point_ptr->x, y=point_ptr->y;
		for(i=0; i<MENU_NUM; i++){
			button_set_bounds(menu_button[i], x, y-30, 100, 30);
	    		y+=30;
	    	}
		
		/* 所有图标重绘 */
    		
		for(i=0; i<MENU_NUM; i++){
			button_repaint(menu_button[i]);
			button_show(menu_button[i]);
	    	}
	    	
		/* 右键菜单显示 */	
		menu_show = 1;
	}
	else{
		for(i=0;i<MENU_NUM;i++){
			button_set_bounds(menu_button[i],0, -30, 0, 0);
		}
	
		desktop_flush();
		
		for(i=0; i<MENU_NUM; i++){
			button_repaint(menu_button[i]);
			button_show(menu_button[i]);
	    	}
		
		/* 右键菜单不显示 */
		menu_show = 0;		
	}
}

void right_click_menu_cancel() {
		si_t i;
		for(i=0;i<MENU_NUM;i++){
			button_set_bounds(menu_button[i],0, -30, 0, 0);
		}
		
		desktop_flush();
			
		for(i=0; i<MENU_NUM; i++){
			button_repaint(menu_button[i]);
			button_show(menu_button[i]);
	    	}
	    		    	
		/* 右键菜单不显示 */
		menu_show = 0;	
}

void desktop_flush(){
	/* 桌面刷新重绘 */
	image_view_reshow(Desktop_im);
  	/* 所有图标重绘 */				
	for(int i=0;i<app_number;i++){
		struct shortcut* sh = vector_at(&sh_desktop_vector, i);
		shortcut_repaint(sh);
		shortcut_show(sh);
	}
}
