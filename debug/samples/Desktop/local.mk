noinst_PROGRAMS += %D%/Desktop

%C%_Desktop_SOURCES = %D%/Desktop.c \
					  %D%/desktop.c \
					  %D%/desktop.h \
					  %D%/taskbar.c \
					  %D%/taskbar.h \
					  %D%/color_base.c \
					  %D%/color_base.h \ 
					  %D%/right_click_menu.h \
					  %D%/right_click_menu.c
%C%_Desktop_LDADD = library/libwidget.la library/libapplication.la library/libwidget.la library/libclient_lib.la library/libgeometry.la library/libcomm.la library/libconfig_parser.la library/libdata_structures.la
