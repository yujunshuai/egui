/**
 * @file window.c
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
# include <stdlib.h>

# include <base_type.h>
# include <config_parser.h>
# include <log.h>
# include <comm.h>
# include <client_lib.h>
# include "compiler.h"

# include "window.h"
# include "paint_window_decoration.h"

/* Invalid path. No specification for window.cfg */
# define TMP_ARRAY_SIZE 256

/* window样式全局对象 */
/* XXX: Not fully implemented.
 * Several attributes are not used.
 */
struct window_style window_default_style = 
{
    {
        /* 初始化，默认未访问 */
        0,  /* .flag */

        /* 默认工作区域 */
        0, 0, 0, 0,

        /* 默认边界宽度 */
        3,  /* .border_size */

        /* 默认宽度&高度 */
        0,  /* .maximum_width */
        0,  /* .minimum_width */
        0,  /* .maximum_height */
        0,  /* .minimum_height */

        /* 默认鼠标形状 */
        CURSOR_SHAPE_X, /* .cursor */

        /* 默认背景色 */
        0, 0, 255, 0,	/* .back_color */

        /* 默认前景色 */
        0, 0, 0, 0,  /* fore_color */
    },

    /* 默认是否可以最大化/最小化/全屏 */
    1,  /* .maximize_enable */
    1,  /* .minimize_enable */
    0,  /* .is_full_screen */

    /* 边框/标题栏尺寸 */
    3,  /* .frame_size */
    30, /* .title_bar_size */

    /** 默认窗口边框颜色 **/
    {0x46, 0xa5, 0xe5, 50},	/* .frame_color */

    /** 菜单栏背景色 **/
    {0x18, 0x29, 0x45, 50},	/* .menu_bar_backcolor */

    /** 菜单栏边框色 **/
    {0xcb, 0xf3, 0xfb, 50},	/* .menu_bar_frame_color */

    /** 标题栏字体颜色 **/
    {0xcc, 0xff, 0x99, 0},	/* .title_bar_font_color */

    /** 标题栏字体大小 **/
    FONT_MATRIX_12	/* .title_font */
};

/**
 * @brief 用window全局样式对象初始化window对象
 *
 * @param style window样式对象指针
 * @param w window指针
 *
 * @return 成功返回0，否则返回-1
 **/
static si_t window_init_with_default_style(struct window * w)
{
    char *config_path = get_config_path("window.cfg");
    char tmp_str[TMP_ARRAY_SIZE] = {'\0'};
    si_t tmp_int;
    struct widget_style_entry extra[] = {
        {.key="maximize_enable", .type=WIDGET_STYLE_TYPE_INT,
            .val=&(window_default_style.maximize_enable)},
        {.key="minimize_enable", .type=WIDGET_STYLE_TYPE_INT,
            .val=&(window_default_style.minimize_enable)},
        {.key="is_full_screen", .type=WIDGET_STYLE_TYPE_INT,
            .val=&(window_default_style.is_full_screen)},

        {.key="frame_size", .type=WIDGET_STYLE_TYPE_INT,
            .val=&(window_default_style.frame_size)},
        {.key="title_bar_size", .type=WIDGET_STYLE_TYPE_INT,
            .val=&(window_default_style.title_bar_size)},

        {.key="frame_color_r", .type=WIDGET_STYLE_TYPE_INT,
            .val=&(window_default_style.frame_color.r)},
        {.key="frame_color_g", .type=WIDGET_STYLE_TYPE_INT,
            .val=&(window_default_style.frame_color.g)},
        {.key="frame_color_b", .type=WIDGET_STYLE_TYPE_INT,
            .val=&(window_default_style.frame_color.b)},
        {.key="frame_color_a", .type=WIDGET_STYLE_TYPE_INT,
            .val=&(window_default_style.frame_color.a)},

        {.key="menu_bar_backcolor_r", .type=WIDGET_STYLE_TYPE_INT,
            .val=&(window_default_style.menu_bar_backcolor.r)},
        {.key="menu_bar_backcolor_g", .type=WIDGET_STYLE_TYPE_INT,
            .val=&(window_default_style.menu_bar_backcolor.g)},
        {.key="menu_bar_backcolor_b", .type=WIDGET_STYLE_TYPE_INT,
            .val=&(window_default_style.menu_bar_backcolor.b)},
        {.key="menu_bar_backcolor_a", .type=WIDGET_STYLE_TYPE_INT,
            .val=&(window_default_style.menu_bar_backcolor.a)},

        {.key="menu_bar_frame_color_r", .type=WIDGET_STYLE_TYPE_INT,
            .val=&(window_default_style.menu_bar_frame_color.r)},
        {.key="menu_bar_frame_color_g", .type=WIDGET_STYLE_TYPE_INT,
            .val=&(window_default_style.menu_bar_frame_color.g)},
        {.key="menu_bar_frame_color_b", .type=WIDGET_STYLE_TYPE_INT,
            .val=&(window_default_style.menu_bar_frame_color.b)},
        {.key="menu_bar_frame_color_a", .type=WIDGET_STYLE_TYPE_INT,
            .val=&(window_default_style.menu_bar_frame_color.a)},

        {.key="title_bar_font_color_r", .type=WIDGET_STYLE_TYPE_INT,
            .val=&(window_default_style.title_bar_font_color.r)},
        {.key="title_bar_font_color_g", .type=WIDGET_STYLE_TYPE_INT,
            .val=&(window_default_style.title_bar_font_color.g)},
        {.key="title_bar_font_color_b", .type=WIDGET_STYLE_TYPE_INT,
            .val=&(window_default_style.title_bar_font_color.b)},
        {.key="title_bar_font_color_a", .type=WIDGET_STYLE_TYPE_INT,
            .val=&(window_default_style.title_bar_font_color.a)},

        {.key="title_font", .type=WIDGET_STYLE_TYPE_STR, .val=tmp_str},
    };

    si_t res = widget_init_with_default_style(config_path,
            WIDGET_POINTER(w), &window_default_style.common,
            extra, sizeof(extra)/sizeof(extra[0]));
    free(config_path);

    if((tmp_int = get_font_enum_from_str(tmp_str)) >= 0) {
        window_default_style.title_font = tmp_int;
    }

    /* 用window默认样式初始化window各样式属性 */
    w->minimize_enable = window_default_style.minimize_enable;
    w->maximize_enable = window_default_style.maximize_enable;
    w->is_full_screen = window_default_style.is_full_screen;

    return res;
}


static si_t window_default_widget_show(struct window * w, union message * msg)
{
    NOT_USED(msg);
    /* 设置区域 */
    set_area
    (w->gd,
     w->area.x - window_default_style.frame_size,
     w->area.y - window_default_style.frame_size - window_default_style.title_bar_size,
     w->area.width + window_default_style.frame_size + window_default_style.frame_size,
     w->area.height + window_default_style.frame_size + window_default_style.frame_size + window_default_style.title_bar_size);

    update(w->gd);
    return 0;
}

static si_t window_default_widget_repaint(struct window * w, union message * msg)
{
    struct rectangle real_area;

    /**************************************************************
     * status:                              paint?
     * WINDOW_STATUS_MAXIMIZED              yes
     * WINDOW_STATUS_NORMAL                 yes
     * WINDOW_STATUS_MINMIZED_NORMAL        no
     * WINDOW_STATUS_MINIMIZED_MAXIMIZED    no
     **************************************************************/
    if(w->status == WINDOW_STATUS_MINMIZED_NORMAL 
        || w->status == WINDOW_STATUS_MINIMIZED_MAXIMIZED)
    {
        return 0;
    }

    if(w->visible)
    {
        area_intersection(&(w->area), &(msg->widget_repaint.area), &real_area);

        /* 设置图形设备的工作区域 */
        set_area
            (w->gd,
             real_area.x,
             real_area.y,
             real_area.width,
             real_area.height);

        /* 使用背景色 */
        set_color
            (w->gd,
             w->back_color.r,
             w->back_color.g,
             w->back_color.b,
             w->back_color.a);

        fill_rectangle
            (w->gd,
             real_area.x,
             real_area.y,
             real_area.width,
             real_area.height);

        /* 绘制装饰性的部分 */
        paint_window_decoration(w);
    }

    return 0;
}

static si_t window_default_widget_move(struct window * w, union message * msg)
{
	si_t screen_h = get_screen_size_h();
	si_t screen_w = get_screen_size_w();
	EGUI_PRINT_INFO("%d,%d\n", msg->base.cursor_position.x,msg->base.cursor_position.y);
	if(msg->base.cursor_position.x==1365){
		w->area.x = screen_w/2;
    w->area.y = 30;
    w->area.width = screen_w/2;
    w->area.height = screen_h-60;
		resize_window
    (w->descriptor,
     w->area.x,
     w->area.y,
     w->area.width,
     w->area.height);
		return 0;
	}
	if(msg->widget_move.position.x==3){
		w->area.x = 3;
    w->area.y = 30;
    w->area.width = screen_w/2;
    w->area.height = screen_h-60;
		resize_window
    (w->descriptor,
     w->area.x,
     w->area.y,
     w->area.width,
     w->area.height);
		return 0;
	}
    /* 更新位置 */
    w->area.x = msg->widget_move.position.x;
    w->area.y = msg->widget_move.position.y;

    move_window
    (w->descriptor,
     w->area.x,
     w->area.y);

    return 0;
}

static si_t window_default_widget_resize(struct window * w, union message * msg)
{
    /* 更新位置 */
    w->area.x = msg->widget_resize.area.x;
    w->area.y = msg->widget_resize.area.y;
    w->area.width = msg->widget_resize.area.width;
    w->area.height = msg->widget_resize.area.height;

    resize_window
    (w->descriptor,
     w->area.x,
     w->area.y,
     w->area.width,
     w->area.height);

    return 0;
}

static si_t window_default_window_minimize(struct window * w, union message * msg)
{
    NOT_USED(msg);
    if(w->minimize_enable == 0)
    {
        return 0;
    }

    /**************************************************************
     * status?                          store?  next status?
     * WINDOW_STATUS_MAXIMIZED          no      WINDOW_STATUS_MINIMIZED_MAXIMIZED
     * WINDOW_STATUS_NORMAL             yes     WINDOW_STATUS_MINMIZED_NORMAL
     * WINDOW_STATUS_MINMIZED_NORMAL    --      --
     * WINDOW_STATUS_MINIMIZED_MAXIMIZED--      --
     **************************************************************/
    if(w->status == WINDOW_STATUS_MAXIMIZED)
    {
        w->status = WINDOW_STATUS_MINIMIZED_MAXIMIZED;
    }
    else if (w->status == WINDOW_STATUS_NORMAL)
    {
        w->restore_area.x = w->area.x;
        w->restore_area.y = w->area.y;
        w->restore_area.width = w->area.width;
        w->restore_area.height = w->area.height;

        w->status = WINDOW_STATUS_MINMIZED_NORMAL;
    }
    else
    {
        return 0;
    }

    minimize_window(w->descriptor);

    return 0;
}

static si_t window_default_window_maximize(struct window * w, union message * msg)
{
    NOT_USED(msg);
    if(w->maximize_enable == 0)
    {
        return 0;
    }

    /**************************************************************
     * status?                          store?      next status?
     * WINDOW_STATUS_MAXIMIZED          --          --
     * WINDOW_STATUS_NORMAL             yes         WINDOW_STATUS_MAXIMIZED
     * WINDOW_STATUS_MINMIZED_NORMAL    --          --
     * WINDOW_STATUS_MINIMIZED_MAXIMIZED--          --
     **************************************************************/
    if(w->status == WINDOW_STATUS_NORMAL)
    {
        w->restore_area.x = w->area.x;
        w->restore_area.y = w->area.y;
        w->restore_area.width = w->area.width;
        w->restore_area.height = w->area.height;

        maximize_window(w->descriptor, &(w->area));

        w->status = WINDOW_STATUS_MAXIMIZED;
    }

    return 0;
}

static si_t window_default_window_restore(struct window * w, union message * msg)
{
    NOT_USED(msg);
    /**************************************************************
     * status?                          restore?    next status?
     * WINDOW_STATUS_MAXIMIZED          yes         WINDOW_STATUS_NORMAL
     * WINDOW_STATUS_NORMAL             --          --
     * WINDOW_STATUS_MINMIZED_NORMAL    yes         WINDOW_STATUS_NORMAL
     * WINDOW_STATUS_MINIMIZED_MAXIMIZEDno          WINDOW_STATUS_MAXIMIZED
     **************************************************************/
    switch(w->status)
    {
    case WINDOW_STATUS_MAXIMIZED:
        w->area.x = w->restore_area.x;
        w->area.y = w->restore_area.y;
        w->area.width = w->restore_area.width;
        w->area.height = w->restore_area.height;
        restore_window(w->descriptor, &w->restore_area);
        w->status = WINDOW_STATUS_NORMAL;
        break;

    case WINDOW_STATUS_NORMAL:
        break;

    case WINDOW_STATUS_MINMIZED_NORMAL:
        w->area.x = w->restore_area.x;
        w->area.y = w->restore_area.y;
        w->area.width = w->restore_area.width;
        w->area.height = w->restore_area.height;
        restore_window(w->descriptor, &w->restore_area);
        w->status = WINDOW_STATUS_NORMAL;
        break;

    case WINDOW_STATUS_MINIMIZED_MAXIMIZED:
        w->status = WINDOW_STATUS_MAXIMIZED;
        maximize_window(w->descriptor, &(w->area));
        break;

    default:
        break;
    }

    return 0;
}

static si_t window_default_window_activate(struct window * w, union message * msg)
{
    /**************************************************************
     * status:                              paint?  restore?
     * WINDOW_STATUS_MAXIMIZED              yes     no
     * WINDOW_STATUS_NORMAL                 yes     no
     * WINDOW_STATUS_MINMIZED_NORMAL        no      yes
     * WINDOW_STATUS_MINIMIZED_MAXIMIZED    no      yes
     **************************************************************/
    if(w->status == WINDOW_STATUS_MINMIZED_NORMAL 
        || w->status == WINDOW_STATUS_MINIMIZED_MAXIMIZED)
    {
        window_default_window_restore(w, msg);
    }

    if(w->visible && !w->is_activated)
    {
        w->is_activated = 1;

        /**
         * only repaint decoration part
         **/
        paint_window_decoration(w);

        window_default_widget_show(w, msg);
    }

    w->is_activated = 1;
    return 0;
}

static si_t window_default_window_deactivate(struct window * w, union message * msg)
{
    NOT_USED(msg);
    /**************************************************************
     * status:                              paint?
     * WINDOW_STATUS_MAXIMIZED              yes
     * WINDOW_STATUS_NORMAL                 yes
     * WINDOW_STATUS_MINMIZED_NORMAL        no
     * WINDOW_STATUS_MINIMIZED_MAXIMIZED    no
     **************************************************************/
    if(w->status == WINDOW_STATUS_MINMIZED_NORMAL 
        || w->status == WINDOW_STATUS_MINIMIZED_MAXIMIZED)
    {
        return 0;
    }

    if(w->visible && w->is_activated)
    {
        si_t x, y, width, height;
        w->is_activated = 0;
        /* 绘制装饰性的部分 */
        paint_window_decoration(w);

        /* 设置图形设备的工作区域 */
        x = w->area.x - window_default_style.frame_size;
        y = w->area.y - window_default_style.frame_size - window_default_style.title_bar_size;
        width = w->area.width + window_default_style.frame_size + window_default_style.frame_size;
        height = w->area.height + window_default_style.frame_size + window_default_style.frame_size + window_default_style.title_bar_size;
        set_area(w->gd, x, y, width, height);

        update(w->gd);
    }
    w->is_activated = 0;
    
    return 0;
}

si_t window_default_callback(addr_t w, addr_t m)
{
    struct window * self = w;
    union message * msg = m;
    
    widget_default_callback(self, msg);

    switch(msg->base.type)
    {
        case MESSAGE_TYPE_WIDGET_SHOW:
        /*
            printf("MESSAGE_TYPE_WIDGET_SHOW\n");
        */
            window_default_widget_show(self, msg);
            break;


        case MESSAGE_TYPE_WIDGET_REPAINT:
        /*
            printf("MESSAGE_TYPE_WIDGET_REPAINT\n");
        */
            window_default_widget_repaint(self, msg);
            window_default_widget_show(self, msg);
            break;

        case MESSAGE_TYPE_WIDGET_MOVE:
        /*
            printf("MESSAGE_TYPE_WIDGET_MOVE\n");
        */
            window_default_widget_move(self, msg);
            break;

        case MESSAGE_TYPE_WIDGET_RESIZE:
        /*
            printf("MESSAGE_TYPE_WIDGET_RESIZE\n");
        */
            window_default_widget_resize(self, msg);
            break;

        case MESSAGE_TYPE_WINDOW_ACTIVATE:
        /*
            printf("MESSAGE_TYPE_WINDOW_ACTIVATE\n");
        */
            window_default_window_activate(self, msg);
            break;

        case MESSAGE_TYPE_WINDOW_DEACTIVATE:
        /*
            printf("MESSAGE_TYPE_WINDOW_DEACTIVATE\n");
        */
            window_default_window_deactivate(self, msg);
            break;

        case MESSAGE_TYPE_WINDOW_MINIMIZE:
        /*
            printf("MESSAGE_TYPE_WINDOW_MINIMIZE\n");
        */
            window_default_window_minimize(self, msg);
            break;

        case MESSAGE_TYPE_WINDOW_MAXIMIZE:
        /*
            printf("MESSAGE_TYPE_WINDOW_MAXIMIZE\n");
        */
            window_default_window_maximize(self, msg);
            break;

        case MESSAGE_TYPE_WINDOW_RESTORE:
        /*
            printf("MESSAGE_TYPE_WINDOW_RESTORE\n");
        */
            window_default_window_restore(self, msg);
            break;

        default:
            break;
    }

    return 0;
}

void window_repaint(struct window* w)
{
	widget_repaint(WIDGET_POINTER(w));
}

void window_show(struct window* w)
{
	widget_show(WIDGET_POINTER(w));
}

struct window* window_init(char* title)
{
    struct window * addr;

    addr = (struct window *)malloc(sizeof(struct window));

    if(addr == NULL)
    {
        EGUI_PRINT_SYS_ERROR("fail to malloc");
        return addr;
    }

    if(!(addr=widget_init_common(WIDGET_POINTER(addr), 0))) {
        return NULL;
    }

    addr->name = "struct window";

    /* 默认是否是窗口 */
    addr->is_window = 1;

    /* default not is_activated */
    addr->is_activated = 0;

    /* default status */
    addr->status = WINDOW_STATUS_NORMAL;

    /* 默认是否是模态 */
    addr->modal = 0;
    /* 默认标题 */
    addr->title = title;
    /* icon path */
    addr->icon_path = NULL;
    //addr->icon_path = "~/egui/resource/icons";

    /* 没注册前的窗口描述符 */
    addr->descriptor = 0;

    /* 用全局样式对象初始化window样式 */
    window_init_with_default_style(addr);

    /* 默认的回调函数 */
    addr->callback = window_default_callback;

    return addr;
}

si_t window_exit(struct window * w)
{
    return widget_exit(WIDGET_POINTER(w));
}

void window_set_bounds(struct window  *w, si_t x, si_t y, si_t width , si_t height)
{
	widget_set_bounds(WIDGET_POINTER(w), x, y, width, height);
}

void window_set_color(struct window* w, struct color* fcolor, struct color* bcolor)
{
	widget_set_color(WIDGET_POINTER(w), fcolor, bcolor);
}
