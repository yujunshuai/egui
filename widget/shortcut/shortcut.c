/**
 * @file shortcut.c
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
# include <stdlib.h>
# include <string.h>
# include <fcntl.h> /* open() */
# include <unistd.h> /* close() */

# include <base_type.h>
# include <config_parser.h>
# include <log.h>
# include <comm.h>
# include <client_lib.h>
# include <graph.h>
# include "compiler.h"
# include "application.h"

# include "shortcut.h"

/* TODO load default parameters like other widgets */

void *shortcut_init(si_t id)
{
    struct shortcut * addr;

    /* 分配存储空间 */
    addr = (struct shortcut *)malloc(sizeof(struct shortcut));

    if(addr == NULL)
    {
        EGUI_PRINT_SYS_ERROR("fail to malloc");
        return NULL;
    }

    if(!(addr=widget_init_common(WIDGET_POINTER(addr), id))) {
        return NULL;
    }
    addr->name = "struct shortcut";

	addr->img_field.x = 0;
	addr->img_field.y = 0;
	addr->img_field.width = 0;
	addr->img_field.height = 0;

	addr->text_field.x = 0;
	addr->text_field.y = 0;
	addr->text_field.width = 0;
	addr->text_field.height = 0;

	addr->is_text_visiable = 0;

	addr->flag = 0;
	addr->is_real = 0;
	addr->position_x=0;
	addr->position_y=0;
	addr->last_do_time.tv_sec=0;
	addr->last_do_time.tv_usec=0;
	
	memset(addr->img_path , 0 ,sizeof(char)*255);
	memset(addr->img_normal_path , 0 ,sizeof(char)*255);
	memset(addr->img_select_path , 0 ,sizeof(char)*255);
	memset(addr->text , 0, sizeof(char)*255);
	memset(addr->app_name , 0, sizeof(char)*30);
	memset(addr->app_path , 0, sizeof(char)*100);
	memset(addr->link_file_path , 0, sizeof(char)*100);
	
	
    /* 默认的回调函数 */
    addr->callback = shortcut_default_callback;

    return addr;
}

/*
 * @breif 本函数功能是通过判断
 *
 */
si_t   shortcut_update_all_areas ( struct shortcut * sh )
{
	struct rectangle area;
	/* 总字数 ， 单字宽度，单字高度，每行字数 ,总行数,最后一行的字数 */
	si_t char_total_num ;
	si_t font_height;
	si_t font_width;
	si_t text_line_num;
	si_t maxlen;

    application_widget_absolute_area(WIDGET_POINTER(sh), &area);


	if(shortcut_get_is_text_visiable(sh) == 1)
	{
		/* 总字数 ， 单字宽度，单字高度 */
		char_total_num = strlen( sh->text );
		font_height = get_font_height( sh->gd ) ;
		font_width  = get_font_width( sh->gd ) ;
		maxlen = area.width * 2 / font_width;

		text_line_num = char_total_num / maxlen + 1;
		if( font_height  > sh->area.height || font_width  >sh->area.width)
		{
            EGUI_PRINT_ERROR("font for desktop shortcut is too large");

        	return -1;
		}

		sh->text_field.x = area.x ;
		sh->text_field.y = area.y + area.height - ( text_line_num * font_height );
		sh->text_field.width = area.width;
		sh->text_field.height = text_line_num * font_height ;

		sh->img_field.x = area.x  ;
		//sh->img_field.x = area.x + area.width/4 ;
		sh->img_field.y = area.y  ;
		sh->img_field.width = area.width ;
		sh->img_field.height = area.height - sh->text_field.height;

	}
	else
	{
		sh->img_field.x = area.x ;
		sh->img_field.y = area.y ;
		sh->img_field.width = area.width ;
		sh->img_field.height = area.height ;
	}
    return 1;
}

/*
 * @breaf private,
 *
 * */



si_t shortcut_draw_img(struct shortcut *sh)
{
	set_area(sh->gd, sh->img_field.x , sh->img_field.y, sh->img_field.width  , sh->img_field.height );

	fill_rectangle(sh->gd, sh->img_field.x , sh->img_field.y, sh->img_field.width  , sh->img_field.height );

	set_color(sh->gd, sh->back_color.r, sh->back_color.g, sh->back_color.b, sh->back_color.a);

	si_t fd;
	if( ( sh->img_path != NULL ) && ( fd = open(sh->img_path , O_RDONLY) )!= -1 )
	{
		draw_img(sh->gd, sh->img_path, ALIGN_HORIZONTAL_TYPE_CENTER | ALIGN_VERTICAL_TYPE_CENTER );
	}

	return 1;
}

si_t shortcut_show_text(struct shortcut * sh)
{

	/* 总字数 ， 单字宽度，单字高度，每行字数 ,总行数,最后一行的字数 */
	si_t char_total_num ;
	si_t font_width;
	si_t font_height;
	si_t maxlen;
	si_t text_line_num;
	si_t last_line_text_num;

	si_t i = 0;


	char_total_num = strlen( sh->text );

	font_width  = get_font_width( sh->gd ) ;

	font_height = get_font_height( sh->gd ) ;

	maxlen = (sh->area.width * 2 )/ font_width;

	last_line_text_num = char_total_num % maxlen ;

	text_line_num = char_total_num / maxlen + 1;

	set_color(sh->gd, sh->fore_color.r, sh->fore_color.g, sh->fore_color.b, sh->fore_color.a);

	/* 设置区域 , 文字区域*/
 	set_area(sh->gd,  sh->text_field.x , sh->text_field.y , sh->text_field.width , sh->text_field.height);

/*	 填充矩形 
	fill_rectangle(sh->gd,  sh->text_field.x, sh->text_field.y, sh->text_field.width , sh->text_field.height);
*  */
	/* 显示文字 */
	for( i = 0; i < text_line_num -1; i++ )
	{
		show_text(sh->gd, sh->text_field.x, sh->text_field.y + i * font_height  , sh->text + i*maxlen ,maxlen);
	}

	show_text(  sh->gd,
			    sh->text_field.x + ( sh->text_field.width  - last_line_text_num * font_width ) / 2,
			    sh->text_field.y + i * font_height  ,
			    sh->text + i * maxlen ,
			    last_line_text_num
			 );
	return 0;

}


si_t
shortcut_exit
(struct shortcut * i)
{
    return widget_exit(WIDGET_POINTER(i));
}
void  shortcut_set_img_path(struct shortcut *sh, char * img_path)
{
	strcpy(sh->img_path,img_path);
}
char* shortcut_get_img_path(struct shortcut *sh)
{
	return sh->img_path;
}

void  shortcut_set_img_normal_path(struct shortcut *sh, char * img_path)
{
	strcpy(sh->img_normal_path,img_path);
	return ;
}
char* shortcut_get_img_normal_path(struct shortcut *sh)
{
	return sh->img_normal_path;
}
void  shortcut_set_img_select_path(struct shortcut *sh, char * img_path)
{
	strcpy(sh->img_select_path,img_path);
	return ;
}
char* shortcut_get_img_select_path(struct shortcut *sh)
{
	return sh->img_select_path;
}

void  shortcut_set_text(struct shortcut *sh, char * text)
{
	strcpy(sh->text, text);
	return;
}
char* shortcut_get_text(struct shortcut *sh)
{
	return sh->text;
}

void  shortcut_set_type(struct shortcut *sh, si_t type)
{
	sh->type = type;
	return ;
}

si_t shortcut_get_type(struct shortcut *sh)
{
	return sh->type;
}
void  shortcut_set_is_text_visiable(struct shortcut *sh, si_t visiable_model)
{
	sh->is_text_visiable = visiable_model;
	return ;
}
si_t shortcut_get_is_text_visiable(struct shortcut *sh)
{
	return sh->is_text_visiable;
}


si_t shortcut_default_callback(void* self , void* msg )
{

    struct shortcut* sh = self;
    union message * m = msg;
    
    widget_default_callback(sh, m);

    switch(m->base.type)
    {
        case MESSAGE_TYPE_WIDGET_REPAINT:
            shortcut_default_widget_repaint(sh, m);
            shortcut_default_widget_show(sh, m);
            break;

        case MESSAGE_TYPE_WIDGET_SHOW:
            shortcut_default_widget_show(sh, m);
            break;

        case MESSAGE_TYPE_MOUSE_PRESS:
            shortcut_default_widget_show(sh, m);
            break;

        case MESSAGE_TYPE_MOUSE_RELEASE:
            shortcut_default_widget_show(sh, m);
            break;

        default:
            break;
    }

    return 0;
}


/* 外部 API */
si_t shortcut_repaint(struct shortcut * sh)
{
  	union message msg;

    msg.widget_repaint.area.x = sh->area.x;
    msg.widget_repaint.area.y = sh->area.y;
    msg.widget_repaint.area.width = sh->area.width;
    msg.widget_repaint.area.height = sh->area.height;

    shortcut_default_widget_repaint(sh, &msg);

    return 0;

}


si_t shortcut_default_widget_repaint(struct shortcut* sh , union message * msg)
{
	NOT_USED(msg);
	shortcut_update_all_areas( sh );

	shortcut_draw_img( sh );

	if(shortcut_get_is_text_visiable(sh) == 1)
	{
		shortcut_show_text(sh);
	}

    return 0;

}

/* 外部API  */
si_t shortcut_show(struct shortcut * sh)
{
  	union message msg;

    msg.widget_repaint.area.x = sh->area.x;
    msg.widget_repaint.area.y = sh->area.y;
    msg.widget_repaint.area.width = sh->area.width;
    msg.widget_repaint.area.height = sh->area.height;

    shortcut_default_widget_show(sh, &msg);

    return 0;

}
/*  */
si_t shortcut_default_widget_show(struct shortcut* sh , union message * msg)
{
	struct rectangle area;
	NOT_USED(msg);

    application_widget_absolute_area(WIDGET_POINTER(sh), &area);
	set_area( sh->gd, area.x, area.y, area.width, area.height );
	update( sh->gd );

	return 0;
}




void shortcut_set_bounds(struct shortcut* shortcut, si_t x, si_t y, si_t width , si_t height)
{
	shortcut->area.x = x;
	shortcut->area.y = y;
	shortcut->area.width = width;
	shortcut->area.height = height;
	return ;
}





