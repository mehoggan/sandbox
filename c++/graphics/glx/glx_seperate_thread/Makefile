all : glx_seperate_thread print_from_thread

glx_seperate_thread : glx_seperate_thread.c
	gcc -pthread -Wall -o glx_seperate_thread glx_seperate_thread.c -lGL -lXext -lX11 -lGLU

print_from_thread : print_from_thread.c
	gcc -pthread -Wall -o print_from_thread print_from_thread.c
