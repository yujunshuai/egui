/**
 * @file desktop.h
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

# ifndef _TASK_BAR_H_
# define _TASK_BAR_H_ 1

# include <base_type.h>
# include <comm.h> 


struct window_info
{
	si_t window_descripter;
	char* title;
};

extern void window_info_init(struct window_info* w, char* title, si_t d);

extern void window_info_exit(struct window_info* w, addr_t arg);


/**
 * 用于判断是否相等
 **/
extern si_t window_info_cmp(addr_t w, addr_t window_descripter);



/**
 * struct desktop_info
 **/
struct desktop_info
{
	struct vector window_info_vector;
};

//声明desktop_info结构体变量desktop
extern struct desktop_info desktop;

extern void desktop_info_init(struct desktop_info* d);


extern void desktop_info_exit(struct desktop_info* d);

extern si_t desktop_info_find_window_num(struct desktop_info* d, si_t window_descripter);
extern struct window_info* desktop_info_find_window(struct desktop_info* d, si_t window_descripter);































# endif
