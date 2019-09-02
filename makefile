CC=gcc
CFLAGS=-I.
DEPS = intial.h
OBJ = myshell.o intial.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

shellcompile: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
