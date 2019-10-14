CC	= gcc
OBJ = mp_div.o
CFLAGS	= -g -O3


all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) 
