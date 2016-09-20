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
 if()
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 * All rights reserved.
 **/
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <stropts.h>
#include <fcntl.h>
#include<time.h>
#include<sys/types.h>
#include<unistd.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>
#include <time.h>
#include "log.h"

# include "start_menu.h"

#include "right_click_menu.h"

/* 开始菜单 */
# define MENU_NUM 2

//开始菜单
static struct button * menu_button[MENU_NUM];//一级菜单
static struct button ** program_button;//二级菜单
static si_t menu_show = 0;//是否显示菜单
static si_t programs_show = 0;//是否显示二级程序菜单
static si_t program_num = 0;//二级菜单中程序的个数
si_t start_menu_screen_h =0 ;//屏幕高度


//获取某个目录下文件个数
si_t get_file_nums(char * path){
	si_t num=0;
	DIR * dir_ptr;
	struct dirent * dirent_ptr;
	dir_ptr=opendir(path);
	chdir(path);
	while((dirent_ptr=readdir(dir_ptr))!=0){
		if(strstr(dirent_ptr->d_name,".shortcut")!=NULL){
			num++;
		}
	}
	chdir("..");
	closedir(dir_ptr);
	return num;
}

//关机按钮回调函数
si_t start_menu_END_callback(void * bt,void * msg){
	switch(message_get_type(msg)){
		case MESSAGE_TYPE_MOUSE_PRESS:
			execl("/home/yu/egui/_bulid/debug/samples/shutdown",NULL);
			break;
		default:
			button_default_callback(bt,msg);
			break;
	}
	return 0;
}

//程序按钮回调函数,显示二级菜单
si_t start_menu_PROGREAMS_callback(void * bt,void * msg){
	switch(message_get_type(msg)){
		case MESSAGE_TYPE_MOUSE_PRESS:
			programs_button_show();
			first_start_menu_show();
			break;
		default :
			button_default_callback(bt,msg);
			break;
	}
	return 0;
}

//应用按钮回调函数,打开应用
si_t program_callback(void * bt,void * msg){
	pid_t id;
	struct button * btn= (struct button *)(bt);
	switch(message_get_type(msg)){
		case MESSAGE_TYPE_MOUSE_PRESS:
			id=fork();
			if(0==id){
				if(strstr(btn->text,"gam")!=NULL){
					execl("/home/yu/egui/_bulid/debug/samples/game",NULL);
				}else if(strstr(btn->text,"fil")!=NULL){
					execl("/home/yu/egui/_bulid/debug/samples/file_browser/file_browser",NULL);
				}else if(strstr(btn->text,"pop")!=NULL){
					execl("/home/yu/egui/_bulid/debug/samples/pop_up_window",NULL);
				}else if(strstr(btn->text,"cal")!=NULL){
					execl("/home/yu/egui/_bulid/debug/samples/calculator/calculator",NULL);
				}else if(strstr(btn->text,"end")!=NULL){
					execl("/home/yu/egui/_bulid/debug/samples/shutdown",NULL);
				}
			}
			start_menu_cancel();
			break;
		default:
			button_default_callback(bt,msg);
			break;
	}
	return 0;
}
//从快捷方式文件夹中获取所有的应用程序并用按钮展示出来
void init_program_button(){
	//快捷方式的目录
	DIR * dir_ptr;
	char  path[]="/home/yu/egui/debug/samples/Desktop/shortcut/";
	//用来保存快捷方式文件的完整路径
	char full_path[1024]={0};
	struct dirent * dirent_ptr;
	//读取文件时保存文件内容的缓冲区
	char content[1024];
	//保存文件信息的结构体
	struct stat file_info;
	//用来读取快捷方式文件
	FILE * fp;
	dir_ptr=opendir(path);
	chdir(path); 
	int num=1;//默认的位置
	if(dir_ptr==NULL){
		return -1;
	}
	char program_name[10]={0};
	si_t i=0;
	while((dirent_ptr=readdir(dir_ptr))!=NULL)	{
		if(strlen(dirent_ptr->d_name)>0&&strcmp(dirent_ptr->d_name,".")!=0&&strcmp(dirent_ptr->d_name,"..")!=0){
			//当前文件是快捷方式文件
			if(strstr(dirent_ptr->d_name,".shortcut")!=NULL){
				si_t j=0;
				//获取程序名字
				while(dirent_ptr->d_name[j]!='.'&&j<10){
					program_name[j]=dirent_ptr->d_name[j];
					j++;
				}
				program_name[j]='\0';
				program_button[i]=button_init(program_name);
				//申请失败
				if(program_button[i]==NULL){
					application_exit();
					return -1;
				}
				//初始化button
				program_button[i]->callback=program_callback;
				button_set_color(program_button[i],&font_white,&ground_purple);
				button_set_bounds(program_button[i],0,-30,0,0);
				object_attach_child(OBJECT_POINTER(Desktop_im),OBJECT_POINTER(program_button[i]));
				i++;
			}	
		}
	}
	chdir("..");
	closedir(dir_ptr);
}


//初始化一级菜单按钮和二级菜单按钮
si_t start_menu_init(){
	start_menu_screen_h=get_screen_size_h();

	//对一级菜单的初始化
	si_t i=0;
	for(i=0;i<MENU_NUM;i++){
		menu_button[i]=NULL;
	}

	menu_button[0]=button_init("ShutDown");
	//申请失败
	if(menu_button[0]==NULL){
		application_exit();
		return -1;
	}
	menu_button[0]->callback=start_menu_END_callback;

	menu_button[1]=button_init("Programs");
	if(menu_button[1]==NULL){
		application_exit();
		return -1;
	}
	menu_button[1]->callback=start_menu_PROGREAMS_callback;

	//添加button到桌面
	for(i=0;i<MENU_NUM;i++){
		button_set_color(menu_button[i],&font_white,&ground_purple);
		button_set_bounds(menu_button[i],0,-30,0,0);
		object_attach_child(OBJECT_POINTER(Desktop_im),OBJECT_POINTER(menu_button[i]));
	}
	menu_show=0;

	//对二级菜单的初始化
	program_num=get_file_nums("/home/yu/egui/debug/samples/Desktop/shortcut/");
	program_button=(struct button**)malloc(sizeof(struct button*)*program_num);
	init_program_button();
}

//处理桌面分发给开始菜单的消息
void start_menu_handle(union message *  msg){
	struct point p = msg->base.cursor_position;
	if(p.x<100&&p.y>start_menu_screen_h-30){
		if(0==menu_show){
			first_start_menu_show();
		}else{
			first_start_menu_cancel();
			programs_button_cancel();
		}
	}else{
		if(p.x<100&&p.y>start_menu_screen_h-90&&p.y<start_menu_screen_h-60){
			first_start_menu_show();
			programs_button_show();
		}else{
			if(1==menu_show){
				first_start_menu_show();
			}
		}
	}
}

//显示二级程序菜单
void programs_button_show(){
	for(int i=0;i<5;i++){
		button_set_bounds(program_button[i],100,start_menu_screen_h-(i+3)*30,100,30);
		button_repaint(program_button[i]);
		button_show(program_button[i]);
	}
	programs_show=1;
}

//显示主开始菜单
void first_start_menu_show(){
	si_t x=0;
	si_t y=start_menu_screen_h-30;
	for(int i=0;i<MENU_NUM;i++){
		button_set_bounds(menu_button[i],x,y-30,100,30); 
		y-=30;
	}

	//所有图标重绘
	for(int i=0;i<MENU_NUM;i++){
		button_repaint(menu_button[i]);
		button_show(menu_button[i]);
	}
	menu_show=1;
}

//隐藏开始菜单
void start_menu_cancel(){
	first_start_menu_cancel();
	programs_button_cancel();
}

//隐藏主开始菜单
void first_start_menu_cancel(){
	si_t i=0;
	for(i=0;i<MENU_NUM;i++){
		button_set_bounds(menu_button[i],0,-30,0,0);
	}

	desktop_flush();

	for(int i=0;i<MENU_NUM;i++){
		button_repaint(menu_button[i]);
		button_show(menu_button[i]);
	}
	menu_show=0;
}

//隐藏程序菜单
void programs_button_cancel(){
	for(int i=0;i<program_num;i++){
		button_set_bounds(program_button[i],0,-30,0,0);
	}
	desktop_flush();
	for(int i=0;i<program_num;i++){
		button_repaint(program_button[i]);
		button_show(program_button[i]);
	}
	programs_show=0;
}

