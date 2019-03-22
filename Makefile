CFLAGS  = -W -Wall -ansi -I /usr/local/include
CC = cc

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

OBJ = UWzone.o check.o resolv.o table.o thread.o

all: $(OBJ)
	$(CC) $(OBJ) -o UWzone -lpthread 
clean:
	rm -f *.o UWzone
