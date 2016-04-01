OBJS = square.o sqcts.o sha1.o ec_vlong.o ec_param.o ec_field.o ec_curve.o ec_crypt.o main.o

CC = gcc
#CFLAGS = -g -Wall -Wextra -Werror -Wunused
CFLAGS = -g -Wall -Wextra -Wunused
INCS = -I.

all: main

main: $(OBJS)
	$(CC) $(CFLAGS) $(INCS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCS) -c -o $@ $^

clean:
	-rm $(OBJS)
	-rm main

.PHONY: clean all
