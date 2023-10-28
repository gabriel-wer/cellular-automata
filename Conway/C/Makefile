CC := clang
CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c11 -Wall -lSDL2_image -lm 
SRCS := main.c
EXEC := tex.out
OBJS := $(SRCS:.c=.o)

all: $(EXEC) clean
$(EXEC): $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm -f $(OBJS)
.PHONY: clean
