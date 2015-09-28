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

# include <assert.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# include <unistd.h>

# include "directory_item.h"
# include "directory_content.h"
# include "my_widget.h"

#include "widget.h"
#include "client_lib.h"
#include "compiler.h"
#include "application.h"

#define DESKTOP_PATH  "/mnt/hgfs/gui/cece/c_egui_desktop/"

static struct color barely_blue = {0xcb, 0xf3, 0xfb, 0};
static struct color light_blue = {0x46, 0xa5, 0xe5, 0};
static struct color white={0xff,0xff,0xff,0};
si_t num =4;
si_t icon_flag=1;
si_t
my_widget_default_widget_show
(struct my_widget * mw,
 union message * msg)
{
    struct rectangle area;
    NOT_USED(msg);

    application_widget_absolute_area(WIDGET_POINTER(mw), &area);

    /* 设置区域 */
    set_area
    (mw->gd,
     area.x,
     area.y,
     area.width,
     area.height);

    /* 更新 */
    update(mw->gd);

    return 0;
}

si_t get_type(char * str)
{
    si_t len=strlen(str);
    si_t i=len-1;
    for(;i>0;i--)
    {
       if(str[i]=='.')
         break;
    }
    if(i==0)
    return 0;
    char key[20] = {'\0'};
    strncpy(key, str+i+1, len-1-i);
    if(strcmp(key,"txt")==0)
    return 1;
    if(strcmp(key,"h")==0)
    return 2;
    if(strcmp(key,"c")==0)
    return 3;
    if(strcmp(key,"cpp")==0)
    return 4;
    if(strcmp(key,"bmp")==0)
    return 5;
    return 0;
}

void get_icon_dir_path(char * icon_path)
{
   if(icon_flag)
   strcpy(icon_path,"/home/wangfei/egui/resource/icons/file_icon/");
   else
   strcpy(icon_path,"/home/wangfei/egui/resource/icons/file_icon2/");
}

si_t fill_icon(struct my_widget * mw,struct directory_item * di_ptr)
{
   char icon_path[200];
   get_icon_dir_path(icon_path);
   if(di_ptr->is_directory == 1)
   { 
      strcat(icon_path,"dir2_1.bmp");              
   }
   else if(di_ptr->is_directory == 2)
   {
      strcat(icon_path,"ex_1.bmp"); 
   }
   else 
   {
      switch(get_type(di_ptr->name))
      {
          case 1:
                 strcat(icon_path,"txt_1.bmp");  
                 break;
          case 2:
                 strcat(icon_path,"h_1.bmp");  
                 break;
          case 3: 
                 strcat(icon_path,"c_1.bmp");  
                 break; 
          case 4:
                 strcat(icon_path,"cpp_1.bmp");  
                 break;
          case 5:
                 strcat(icon_path,"bmp_1.bmp");  
                 break; 
          default:
                 strcat(icon_path,"unknow_1.bmp");  
                 break;  
       }
    }
   draw_img(mw->gd,icon_path, ALIGN_HORIZONTAL_TYPE_CENTER | ALIGN_VERTICAL_TYPE_CENTER );
   return 0;

}

si_t fill_icon_2(struct my_widget * mw,struct directory_item * di_ptr)
{
   char icon_path[200];
   get_icon_dir_path(icon_path);
   if(di_ptr->is_directory == 1)
   { 
      strcat(icon_path,"dir2_2.bmp");              
   }
   else if(di_ptr->is_directory == 2)
   {
      strcat(icon_path,"ex_2.bmp"); 
   }
   else 
   {
      switch(get_type(di_ptr->name))
      {
          case 1:
                 strcat(icon_path,"txt_2.bmp");  
                 break;
          case 2:
                 strcat(icon_path,"h_2.bmp");  
                 break;
          case 3: 
                 strcat(icon_path,"c_2.bmp");  
                 break; 
          case 4:
                 strcat(icon_path,"cpp_2.bmp");  
                 break;
          case 5:
                 strcat(icon_path,"bmp_2.bmp");  
                 break; 
          default:
                 strcat(icon_path,"unknow_2.bmp");  
                 break;  
               }
           }
   draw_img(mw->gd,icon_path, ALIGN_HORIZONTAL_TYPE_CENTER | ALIGN_VERTICAL_TYPE_CENTER );
   return 0;
}


si_t
my_widget_default_widget_repaint
(struct my_widget * mw,
 union message * msg)
{
    struct directory_item * di_ptr;
    struct rectangle area;
    si_t x, y, font_height, i, n, x1, y1, temp;
    NOT_USED(msg);

    /* 获得左上角的绝对坐标 */
    widget_absolute_coordinate(WIDGET_POINTER(mw), &x, &y);

    /* 获得绝对的工作区域 */
    /* 将会舍弃不在父控件内的部分*/
    application_widget_absolute_area(WIDGET_POINTER(mw), &area);

    /* 设置区域 */
    set_area
    (mw->gd,
     area.x,
     area.y,
     area.width,
     area.height);

    set_color
    (mw->gd,
     mw->back_color.r,
     mw->back_color.g,
     mw->back_color.b,
     mw->back_color.a);

    fill_rectangle
    (mw->gd,
     area.x,
     area.y,
     area.width,
     area.height);

    /**
     * draw frame
     **/
    set_color
    (mw->gd,
     mw->frame_color.r,
     mw->frame_color.g,
     mw->frame_color.b,
     mw->frame_color.a);
    draw_rectangle
    (mw->gd,
     area.x,
     area.y,
     area.width,
     area.height);
    draw_rectangle
    (mw->gd,
     area.x + 1,
     area.y + 1,
     area.width - 2,
     area.height - 2);

    area.x += 5;
    area.y += 5;
    area.width -= 10;
    area.height -= 10;
    x += 5;
    y += 5;

    set_color
    (mw->gd,
     mw->fore_color.r,
     mw->fore_color.g,
     mw->fore_color.b,
     mw->fore_color.a);

    set_font(mw->gd, mw->font);
    /* 获得字体的高度 */
    font_height = get_font_height(mw->gd);

    n = (si_t)vector_size(&file_list);

    x1 = x ;
    y1 = y ;
    char file_name[15]="";
    /* 目录项开始的索引 */
        temp = mw->start;
    if(n -temp> mw->count)
    n=mw->count;
    else
    n=n -temp;
    for(i = 0; i <n; ++ i)
        {
            memset(file_name,0,sizeof(file_name));
            di_ptr = vector_at(&file_list, temp ++);
            set_area(mw->gd,x1+110*(i%num)+30,y1+90*(i/num)+15,60,58);
            set_color(mw->gd,mw->back_color.r,mw->back_color.g, mw->back_color.b,mw->back_color.a);
            fill_icon(mw,di_ptr);

           set_area(mw->gd,area.x,area.y,area.width,area.height);
           set_color(mw->gd,mw->fore_color.r,mw->fore_color.g,mw->fore_color.b, mw->fore_color.a);
             if(strlen(di_ptr->name)>12)
             {
               strncpy(file_name, di_ptr->name+2, 9);
               strncpy(file_name+9, "...", 3);
             }
             else
                strcpy(file_name, di_ptr->name+2);  
            show_text
            (mw->gd,
             x1+110*(i%num)+30-(strlen(file_name) - 7)*4,
             y1+90*(i/num)+60+12,
             file_name,
             strlen(file_name));
        }
    /* 目录项的数目大于能显示的数目 *//*
    if(n -temp> mw->count)
    {
        
        for(i = 0; i < mw->count; ++ i)
        {
            memset(file_name,0,sizeof(file_name));
            di_ptr = vector_at(&file_list, temp ++);
            set_area(mw->gd,x1+110*(i%num)+30,y1+90*(i/num)+15,60,58);
            set_color(mw->gd,mw->back_color.r,mw->back_color.g, mw->back_color.b,mw->back_color.a);
            fill_icon(mw,di_ptr);

           set_area(mw->gd,area.x,area.y,area.width,area.height);
           set_color(mw->gd,mw->fore_color.r,mw->fore_color.g,mw->fore_color.b, mw->fore_color.a);
             if(strlen(di_ptr->name)>12)
             {
               strncpy(file_name, di_ptr->name+2, 9);
               strncpy(file_name+9, "...", 3);
             }
             else
                strcpy(file_name, di_ptr->name+2);  
            show_text
            (mw->gd,
             x1+110*(i%num)+30-(strlen(file_name) - 7)*4,
             y1+90*(i/num)+60+12,
             file_name,
             strlen(file_name));
        }
    }
    else
    {
        for(i = 0; i < n -temp; ++ i)
        {
            memset(file_name,0,sizeof(file_name));
            di_ptr = vector_at(&file_list, temp+i);
            set_area(mw->gd,x1+110*(i%num)+30,y1+90*(i/num)+15,60,58);
            set_color(mw->gd,mw->back_color.r,mw->back_color.g, mw->back_color.b,mw->back_color.a);
           fill_icon(mw,di_ptr);


           set_area(mw->gd,area.x,area.y,area.width,area.height);
           set_color(mw->gd,mw->fore_color.r,mw->fore_color.g,mw->fore_color.b, mw->fore_color.a);
             if(strlen(di_ptr->name)>12)
             {
               strncpy(file_name, di_ptr->name+2, 9);
               strncpy(file_name+9, "...", 3);
             }
             else
                strcpy(file_name, di_ptr->name+2);  
            show_text
            (mw->gd,
             x1+110*(i%num)+30-(strlen(file_name) - 7)*4,
             y1+90*(i/num)+60+12,
             file_name,
             strlen(file_name));

        }
    }
*/
    return 0;
}

si_t
my_widget_default_mouse_press
(struct my_widget * mw,
 union message * msg)
{
    struct rectangle area;
    si_t x, y, x1,y1, index;
    struct directory_item * di_ptr;

    if(msg->mouse.code == INPUT_CODE_MOUSE_L_KEY)
    {
        /* 获得左上角的绝对坐标 */
        widget_absolute_coordinate(WIDGET_POINTER(mw), &x, &y);

        /* 获得绝对的工作区域 */
        /* 将会舍弃不在父控件内的部分*/
        application_widget_absolute_area(WIDGET_POINTER(mw), &area);

        my_widget_repaint(mw);
        my_widget_show(mw);
        
        /* 双击了那个目录项 */
        y1 = msg->mouse.cursor_position.y - y;
        x1 = msg->mouse.cursor_position.x - x;
        if(x1<110*((x1-30)/110)+30-1||x1>110*((x1-30)/110)+100-1||y1<90*((y1-15)/90)+15+2||y1>90*((y1-15)/90)+78+2)
           return 0;

        index = (y1-15)/90*num +(x1-30)/110;
        if(index >= (si_t)vector_size(&file_list))
           return 0;
         di_ptr = vector_at(&file_list, index + mw->start);
         set_area(mw->gd,x+5+110*(index%num)+30,y+5+90*(index/num)+15,60,60);
         set_color(mw->gd,mw->back_color.r,mw->back_color.g, mw->back_color.b,mw->back_color.a);
         fill_icon_2(mw,di_ptr);       
    }
    return 0;
}

si_t
my_widget_default_mouse_release
(struct my_widget * mw,
 union message * msg)
{
    struct rectangle area;
    si_t x, y, x1,y1, index;

    if(msg->mouse.code == INPUT_CODE_MOUSE_L_KEY)
    {
        /* 获得左上角的绝对坐标 */
        widget_absolute_coordinate(WIDGET_POINTER(mw), &x, &y);

        /* 获得绝对的工作区域 */
        /* 将会舍弃不在父控件内的部分*/
        application_widget_absolute_area(WIDGET_POINTER(mw), &area);

        /* 双击了那个目录项 */
        y1 = msg->mouse.cursor_position.y - y;
        x1 = msg->mouse.cursor_position.x - x;
        if(x1<110*((x1-30)/110)+30-1||x1>110*((x1-30)/110)+100-1||y1<90*((y1-15)/90)+15+2||y1>90*((y1-15)/90)+78+2)
           return 0;
        index = (y1-15)/90*num +(x1-30)/110;
        if(index >= (si_t)vector_size(&file_list))
           return 0;
    }
    return 0;
}

si_t
my_widget_default_mouse_double_click
(struct my_widget * mw,
 union message * msg)
{
    struct rectangle area;
    struct directory_item * di_ptr;
    si_t x, y, x1,y1, index;

    if(msg->mouse.code == INPUT_CODE_MOUSE_L_KEY)
    {
        /* 获得左上角的绝对坐标 */
        widget_absolute_coordinate(WIDGET_POINTER(mw), &x, &y);

        /* 获得绝对的工作区域 */
        /* 将会舍弃不在父控件内的部分*/
        application_widget_absolute_area(WIDGET_POINTER(mw), &area);

        /* 双击了那个目录项 */
        y1 = msg->mouse.cursor_position.y - y;
        x1 = msg->mouse.cursor_position.x - x;
   
         set_color(mw->gd, 255, 255, 255, 0);


        index = (y1-15)/90*num +(x1-30)/110;
        if(index >= (si_t)vector_size(&file_list))
            return 0;

        di_ptr = vector_at(&file_list, index + mw->start);

        /* 双击的是路径 */
        if(di_ptr->is_directory == 1)
        {
            chdir(di_ptr->name + 2);

            getcwd(working_directory, PATH_MAX);

            vector_clear(&file_list);

            directory_content(working_directory, &file_list);

            mw->start = 0;

            scroll_bar_set_view(s, 90 * ((vector_size(&file_list)-1)/num+2), 0);
            scroll_bar_update_offset(s, 0);
            scroll_bar_repaint(s);
            scroll_bar_show(s);

            label_repaint(l);
            label_show(l);

            my_widget_repaint(mw);
            my_widget_show(mw);
        }
        /**
         * executable regular file
         **/
        else if(di_ptr->is_directory == 2)
        {
            char* command[2];
            char all_path[PATH_MAX];
            pid_t pid;
            command[0] = di_ptr->name + 2;
            command[1] = NULL;
            strncpy(all_path, working_directory, PATH_MAX);
            strncat(all_path, di_ptr->name + 2, PATH_MAX);
            if((pid = fork()) == 0)
            {
                execv(command[0], command);
                exit(0);
            }
        }
        else if(di_ptr->is_directory == 3)
        {
            pid_t pid; 
            if(get_type(di_ptr->name)==5)
           {
               char file_name[100];
               si_t item=0;
               strncpy(file_name,working_directory,100);
               item=strlen(file_name);
               file_name[item]='/';
               file_name[item+1]='\0';
               strncat(file_name,di_ptr->name+2,100);
               if((pid = fork()) == 0)
              {
                set_color(mw->gd, 0, 0, 0, 0);
                execl("/home/wangfei/egui/_bulid/debug/samples/image_view","./image_view",file_name,NULL);
                exit(0);
              }

           }
            
            else
           {
               if((pid = fork()) == 0)
              {
                set_color(mw->gd, 0, 0, 0, 0);
                //execv(command[0], command);
                 // execl("/home/wangfei/egui/_build/debug/samples/editerbasic","./editerbasic",NULL);
                  execl("/home/wangfei/egui/_bulid/debug/samples/editerbasic","./editerbasic",di_ptr->name+2,NULL);
                  //execl(command[0],command);
                exit(0);
              }
           } 
        }
    }

    return 0;
}

si_t
my_widget_default_callback
(void * self,
 void * msg)
{
    struct my_widget * mw = self;
    union message * m = msg;

    switch(m->base.type)
    {
        case MESSAGE_TYPE_WIDGET_REPAINT:
            my_widget_default_widget_repaint(mw, m);
            my_widget_default_widget_show(mw, m);
            break;

        case MESSAGE_TYPE_WIDGET_SHOW:
            my_widget_default_widget_show(mw, m);
            break;

        case MESSAGE_TYPE_MOUSE_PRESS:
            my_widget_default_mouse_press(mw, m);
            my_widget_default_widget_show(mw, m);
            break;

        case MESSAGE_TYPE_MOUSE_RELEASE:
            my_widget_default_mouse_release(mw, m);
            my_widget_default_widget_show(mw, m);
            break;

        case MESSAGE_TYPE_MOUSE_SINGLE_CLICK:
            //my_widget_default_mouse_single_click(mw, m);
            break;
        
        case MESSAGE_TYPE_MOUSE_DOUBLE_CLICK:
            my_widget_default_mouse_double_click(mw, m);
            break;

        case MESSAGE_TYPE_WINDOW_CLOSE:
            vector_exit(&file_list);
            break;

        default:
            break;
    }

    return 0;
}

si_t
my_widget_repaint
(struct my_widget * mw)
{
    union message msg;

    msg.widget_repaint.area.x = mw->area.x;
    msg.widget_repaint.area.y = mw->area.y;
    msg.widget_repaint.area.width = mw->area.width;
    msg.widget_repaint.area.height = mw->area.height;

    my_widget_default_widget_repaint(mw, &msg);

    return 0;
}

si_t
my_widget_show
(struct my_widget * mw)
{
    union message msg;

    msg.widget_repaint.area.x = mw->area.x;
    msg.widget_repaint.area.y = mw->area.y;
    msg.widget_repaint.area.width = mw->area.width;
    msg.widget_repaint.area.height = mw->area.height;

    my_widget_default_widget_show(mw, &msg);

    return 0;
}

void *
my_widget_init
(si_t id)
{
    struct my_widget * addr;

    /* 分配存储空间 */
    addr = (struct my_widget *)malloc(sizeof(struct my_widget));

    if(addr == NULL)
    {
        printf("ERROR AT LINE %d OF FILE %s\n", __LINE__, __FILE__);
        perror("malloc");

        return NULL;
    }

    /* 申请图形设备 */
    addr->gd = graphics_device_init(0, 0, 0, 0, 0, 0 ,0 ,0 ,0);

    /* 申请失败 */
    if(addr->gd == 0)
    {
        /* 释放存储空间 */
        free(addr);

        return NULL;
    }

    /* struct button 的成员 */
    addr->parent = NULL;
    addr->lchild = NULL;
    addr->rchild = NULL;
    addr->name = "struct my_widget";
    addr->id = id;

    /* 默认工作区域 */
    addr->area.x = 0;
    addr->area.y = 0;
    addr->area.width = 0;
    addr->area.height = 0;

    /* 默认边界宽度 */
    addr->border_size = 0;

    /* 默认最大宽度 */
    addr->maximum_width = 0; /* should use macro */
    /* 默认最大高度 */
    addr->maximum_height = 0; /* should use macro */
    /* 默认最小宽度 */
    addr->minimum_width = 0;
    /* 默认最小高度 */
    addr->minimum_height = 0;

    /* 默认鼠标形状 */
    addr->cursor = CURSOR_SHAPE_X;

    /* 默认是否能处理键盘输入消息 */
    addr->input_enable = 0;

    /* 默认是否可以刷新 */
    addr->update_enable = 1;

    /* 默认是否可见 */
    addr->visible = 1;

    /* 默认是否拥有键盘焦点*/
    addr->keybd_focus = 0;

    /* 默认是否是窗口 */
    addr->is_window = 0;

    //addr->back_color = barely_blue;
    addr->frame_color = light_blue;
    addr->back_color = white;
    addr->font = FONT_MATRIX_08;

    /* 默认的回调函数 */
    addr->callback = my_widget_default_callback;
   
    icon_flag=0;

    return addr;
}

/*
    如果对象在对象树中就不应该调用，
    application 会自动为你释放相应的资源，
    如果不在对象树中，你可以调用这个函数。
*/
si_t
my_widget_exit
(struct my_widget * mw)
{
    graphics_device_exit(mw->gd);

    free(mw);

    return 0;
}
