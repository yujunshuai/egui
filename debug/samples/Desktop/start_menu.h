
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
# ifndef _RIGHT_CLICK_MENU_H_
# define _RIGHT_CLICK_MENU_H_ 1

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <base_type.h>
# include <comm.h> 
# include <widget.h>

# include "geometry.h"
# include "comm.h"
# include "application.h"
# include "client_lib.h"
# include "widget.h"

# include "color_base.h"

# include "color.h"



si_t start_menu_init();

void start_menu_handle(union message* msg);

void start_menu_cancel();


# endif
