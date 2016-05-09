#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "geometry.h"
#include "comm.h"
#include "application.h"
#include "client_lib.h"
#include "widget.h"

#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include "log.h"

static struct color light_green = {0xcc, 0xff, 0x99, 0};
static struct color barely_blue = {0xcb, 0xf3, 0xfb, 0};

struct button *b = NULL;

void update_time_handler();

//si_t button_callback(void *b, void *msg)	{
//	pthread_t pid;
//	switch(message_get_type(msg)){
//		case MESSAGE_TYPE_MOUSE_SINGLE_CLICK:
//			EGUI_PRINT_INFO("button receive the single_click_msg\n");
//			pthread_create(&pid, NULL, update_time, (void *)b);
//	//		button_set_color(b, NULL, &light_green);
//	//		button_set_text(b,"test");
//	//		button_repaint(b);
//
//		break;
//		default:
//			button_default_callback(b,msg);
//			break;
//	}
//	return 0;
//}

void update_time_handler(){
	EGUI_PRINT_INFO("button deal the single_click_msg\n");
	time_t rawtime;
	struct tm * timeinfo;

	while(1){			
		EGUI_PRINT_INFO("UPDATE THE TIME\n");
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		button_set_text(b, asctime(timeinfo));
	//	button_set_color(b, NULL, &light_green);
		button_repaint(b);
		sleep(1);
	}

}

int main(){
	si_t video_access_mode = VIDEO_ACCESS_MODE_BUFFER;
	si_t app_type = APPLICATION_TYPE_TIMER;
	struct window *w = NULL;
	application_init(video_access_mode, app_type,"time");

	si_t screen_w = get_screen_size_w();
	si_t screen_h = get_screen_size_h();

	w = window_init("time");
	window_set_bounds(w,screen_w-200,screen_h-15,200,15);
	window_set_color(w,NULL,&light_green);

	b = button_init("time");
	button_set_bounds(b,0,0,200,15);
	button_set_color(b,NULL,&barely_blue);
	button_set_text(b, "test text");
//	b->callback = button_callback;

	object_attach_child(OBJECT_POINTER(w), OBJECT_POINTER(b));
	application_add_window(NULL,w);
	application_set_main_window(w);

//	pthread_t pid;
//	pthread_create(&pid,NULL,update_time,(void*)b);
//	EGUI_PRINT_INFO("create a thread\n");
//
//	pid_t pid;
//	if(pid=fork()==0){
//		sleep(3);
	//	update_time(b);
//	}else{
	//	application_exec();
//	}

	application_set_update_time(update_time_handler);
		application_exec();
}
