OBJS = main.o time.o utils.o

all: $(OBJS)
	gcc $(OBJS)