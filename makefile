CC = gcc

all: rate_leam

rate_leam: rate_leam.c

	$(CC) -o    rate_leam   rate_leam.c

clean:

	rm  -f  rate_leam.c
