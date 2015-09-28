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

# include <stdio.h>
# include <string.h>
# include <unistd.h>

# include "application.h"
# include "widget.h"

#define N 16
struct color backgroud_col = {0xB7, 0xf0, 0xF7, 0};
struct color normal_col = {0x3E, 0x8B, 0xEF, 0};
struct color select_col = {0x5C, 0x3D, 0xAF, 0};
struct button *bb[N];
struct color col[2];
int bbc[N]={0};
int i=100;
int j=0;

void set_allcolor(){
	int i=0;
	for(i=0;i<N;i++){
		button_set_color(bb[i],NULL,&col[bbc[i]]);
		button_repaint(bb[i]);
	}
}

int end(){
	int sum=0,i=0;
	for(i=0;i<N;i++)
		sum+=bbc[i];
	if(sum==16||sum==0)return 1;
	else return 0;
}
	


//callback函数
si_t
button_callback
(void * btn,void * msg)
{
	struct button * b = btn;
	struct button * b1 = btn;
	int n=b->fore_color.r;
	if(message_get_type(msg)==MESSAGE_TYPE_MOUSE_SINGLE_CLICK){
		switch(n){
			case 5:case 6:case 9:case 10:
				bbc[n]=(bbc[n]+1)%2;bbc[n+1]=(bbc[n+1]+1)%2;bbc[n-1]=(bbc[n-1]+1)%2;		
				bbc[n-4]=(bbc[n-4]+1)%2;bbc[n+4]=(bbc[n+4]+1)%2;break;
			case 0: bbc[n]=(bbc[n]+1)%2;bbc[n+1]=(bbc[n+1]+1)%2;bbc[n+4]=(bbc[n+4]+1)%2;break;
			case 3: bbc[n]=(bbc[n]+1)%2;bbc[n-1]=(bbc[n-1]+1)%2;bbc[n+4]=(bbc[n+4]+1)%2;break;
			case 12: bbc[n]=(bbc[n]+1)%2;bbc[n+1]=(bbc[n+1]+1)%2;bbc[n-4]=(bbc[n-4]+1)%2;break;
			case 15: bbc[n]=(bbc[n]+1)%2;bbc[n-1]=(bbc[n-1]+1)%2;bbc[n-4]=(bbc[n-4]+1)%2;break;
			case 1:case 2:
				bbc[n]=(bbc[n]+1)%2;bbc[n+1]=(bbc[n+1]+1)%2;bbc[n-1]=(bbc[n-1]+1)%2;bbc[n+4]=(bbc[n+4]+1)%2;break;	
			case 4:case 8:
				bbc[n]=(bbc[n]+1)%2;bbc[n+1]=(bbc[n+1]+1)%2;bbc[n-4]=(bbc[n-4]+1)%2;bbc[n+4]=(bbc[n+4]+1)%2;break;
			case 7:case 11:
				bbc[n]=(bbc[n]+1)%2;bbc[n-1]=(bbc[n-1]+1)%2;bbc[n-4]=(bbc[n-4]+1)%2;bbc[n+4]=(bbc[n+4]+1)%2;break;
			case 13:case 14:
				bbc[n]=(bbc[n]+1)%2;bbc[n+1]=(bbc[n+1]+1)%2;bbc[n-1]=(bbc[n-1]+1)%2;bbc[n-4]=(bbc[n-4]+1)%2;break;				
		}
		set_allcolor();
		if(end()){
			struct window * ww;
		    /* 申请窗口 */
		    ww = window_init("You win!");
		    /* 申请失败 */
		    if(ww == NULL)
	        {
	  	      application_exit();
		      return -1;
		    }
			window_set_bounds(ww, 200, 100, 250, 100);
			window_set_color(ww, NULL, &col[0]);

		    /* 添加子窗口 */
            application_add_window(global_application.main_window, ww);
		}
	}

	else
		button_default_callback(b, msg);
}



int main()
{
	int k;
    si_t video_access_mode = VIDEO_ACCESS_MODE_BUFFER;
	si_t app_type = APPLICATION_TYPE_NORMAL;
	col[0] = normal_col;
	col[1] = select_col;
 	struct window * w;

    /* 初始化用户应用程序 */
    application_init(video_access_mode, app_type, "game");

    /* 申请窗口 */
    w = window_init("game");
    /* 申请失败 */
    if(w == NULL)
    {
        application_exit();
        return -1;
    }
	window_set_bounds(w, 200, 100, 300, 300);
	window_set_color(w, NULL, &backgroud_col);
    

	for(j=0;j<N;j++){
    	bb[j]= button_init("");
    	/* 申请失败 */
    	if(bb[j] == NULL)
    	{
        	application_exit();
        	return -1;
    	}
		button_set_bounds(bb[j], (j%4)*75, (j/4)*75, 73, 73);
		button_set_color(bb[j], NULL, &normal_col);
		bb[j]->fore_color.r=j;
    	bb[j]->callback = button_callback;
	}

	for(j=0;j<N;j++)
		object_attach_child(OBJECT_POINTER(w), OBJECT_POINTER(bb[j]));
	

    /* 添加顶层窗口 */
    application_add_window(NULL, w);

    /* 设置主窗口 */
    application_set_main_window(w);

    /* 运行 */
    application_exec();


    return 0;
}
