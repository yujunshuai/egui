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
# ifndef _DESKTOP_TOOL_H_
# define _DESKTOP_TOOL_H_ 1

# include <base_type.h>

# include "color.h"

extern struct color light_red;

extern struct color light_green;
extern struct color friut_green;

extern struct color barely_blue;
extern struct color xue_blue;
extern struct color heavy_blue;
extern struct color bar_blue;
extern struct color ground_purple;

extern struct color font_white;

//以下为Desktop.c 和其他文件会用到的外部全局变量，事先声明
extern int app_number;
extern struct image_view * Desktop_im;
extern struct vector sh_desktop_vector;
extern si_t area_num_x;
extern si_t area_num_y;
extern int** flag_pptr;
extern struct rectangle** area_pptr;
extern struct window * Desktop_w;

extern si_t shortcut_callback(void * sh, void * msg);











# endif
