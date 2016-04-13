OBJS = ./pegwit/src/sha1.o ./pegwit/src/ec_vlong.o ./pegwit/src/ec_param.o ./pegwit/src/ec_field.o ./pegwit/src/ec_curve.o ./pegwit/src/ec_crypt.o main.o

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -Wunused
INCS = -I. -I./pegwit/inc

all: main

main: $(OBJS)
	$(CC) $(CFLAGS) $(INCS) -lssl -lcrypto -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCS) -c -o $@ $^

clean:
	-rm $(OBJS)
	-rm main

.PHONY: clean all
