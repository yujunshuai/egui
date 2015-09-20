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


# include "taskbar.h"


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


void desktop_info_init(struct desktop_info* d)
{
	vector_init(&d->window_info_vector);
}

void desktop_info_exit(struct desktop_info* d)
{
	vector_for_each(&d->window_info_vector, NULL, window_info_exit);
}

si_t desktop_info_find_window_num(struct desktop_info* d, si_t window_descripter){
	si_t i = vector_find(&d->window_info_vector, window_descripter, window_info_cmp);
	return i;
}

struct window_info* desktop_info_find_window(struct desktop_info* d, si_t window_descripter)
{
	si_t i = vector_find(&d->window_info_vector, window_descripter, window_info_cmp);
	return (struct window_info*)vector_at(&d->window_info_vector, i);
}





