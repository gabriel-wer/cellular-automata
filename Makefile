conway: conway.c
	gcc conway.c -o main -Wall -Wextra


## A simple Makefile for compiling small SDL projects
#
## set the compiler
#CC := clang
#
## set the compiler flags
#CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lm
## add header files here
#HDRS :=
#
## add source files here
#SRCS := teste.c
#
## generate names of object files
#OBJS := $(SRCS:.c=.o)
#
## name of executable
#EXEC := tex
#
## default recipe
#all: $(EXEC)
# 
#showfont: showfont.c Makefile
#	$(CC) -o $@ $@.c $(CFLAGS) $(LIBS)
#
#glfont: glfont.c Makefile
#	$(CC) -o $@ $@.c $(CFLAGS) $(LIBS)
#
## recipe for building the final executable
#$(EXEC): $(OBJS) $(HDRS) Makefile
#	$(CC) -o $@ $(OBJS) $(CFLAGS)
#
## recipe to clean the workspace
#clean:
#	rm -f $(EXEC) $(OBJS)
#
#.PHONY: all clean
