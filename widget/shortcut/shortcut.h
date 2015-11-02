/**
 * @file shortcut.h
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

# ifndef _SHORTCUT_H_
# define _SHORTCUT_H_ 1

# include <base_type.h>
# include <comm.h>

# include "../widget/widget.h"

/**
 * 窗口部件结构体
 **/
# define SHORTCUT_DEFINITION \
    /**
     * 从 widget 继承
    **/ \
    WIDGET_DEFINITION


/*
 *@brief  shortcut 控件
 *@param img_path 图标中图片的存放路径
 *@param text     图标的名称，即文本
 *@param type     图标类型
 *
 * 包括普通文件图标、目录文件图标等等，详细请参看 /src/data/enumerator/shortcut_type. 
 * 这里 / 代表Egui工程根目录。
 *
 *@param is_text_visiable 图标是否显示文本内容。
 *@param text_field 图标中的文本区域，即图标中 文本的画布区域。
 *@param img_field  图标中的图片区域，即图标中 图片的画布区域。
 *
*/
struct shortcut
{
    SHORTCUT_DEFINITION
	char img_path[255];
	char img_normal_path[255]; 
	char img_select_path[255];
	char text[255];
	char app_name[30];
	char app_path[100];
	char link_file_path[100];
	/* see the enum shortcut_type */
	si_t type;
	si_t is_text_visiable;
	si_t flag;
	
	si_t position_x;
	si_t position_y;
	struct timeval last_do_time;
	
	
	struct rectangle text_field;
	struct rectangle img_field;

};

/**
 * 将地址强制转换成 struct shortcut *
**/
# define SHORTCUT_POINTER(addr) ((struct shortcut *)(addr))


extern void  shortcut_set_img_path(struct shortcut *sh, char * img_path);
extern char* shortcut_get_img_path(struct shortcut *sh);

extern void  shortcut_set_img_normal_path(struct shortcut *sh, char * img_path);
extern char* shortcut_get_img_normal_path(struct shortcut *sh);

extern void  shortcut_set_img_select_path(struct shortcut *sh, char * img_path);
extern char* shortcut_get_img_select_path(struct shortcut *sh);

extern void  shortcut_set_text(struct shortcut *sh, char * text);
extern char* shortcut_get_text(struct shortcut *sh);



extern void  shortcut_set_type(struct shortcut *sh, si_t type);
extern si_t  shortcut_get_type(struct shortcut *sh);

extern void  shortcut_set_is_text_visiable(struct shortcut *sh, si_t visiable_model);
extern si_t  shortcut_get_is_text_visiable(struct shortcut *sh);



extern si_t shortcut_default_callback(void* self , void* msg );

/**
 * @brief 使用前,设置窗口部件结构体
 *
 * @details
 *
 * @param id 窗口部件的标识符
 *
 * @return 0
**/
extern void * shortcut_init(si_t id);


/**
 * @brief 使用后清理窗口部件结构体
 *
 * @details
 *
 * @param i 窗口部件结构体指针
 *
 * @return 0
**/
extern si_t shortcut_exit (struct shortcut * sh);

/**
 * 绘制窗口部件
 *
 * @param i 窗口部件的地址
 *
 * @return 0
**/
extern void shortcut_set_bounds(struct shortcut *sh, si_t x, si_t y, si_t width , si_t height);

extern si_t shortcut_repaint(struct shortcut * i);
extern si_t shortcut_default_widget_repaint(struct shortcut* sh , union message * msg);


extern si_t shortcut_show_text(struct shortcut * i);

extern si_t shortcut_show(struct shortcut * i);
extern si_t shortcut_default_widget_show(struct shortcut* sh , union message * msg);


# endif
