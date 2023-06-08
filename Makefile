# Copyright 2022 Nastase Cristian-Gabriel 315CA

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS = my_octave

build: $(TARGETS)

my_octave: my_octave.c
	$(CC) $(CFLAGS) my_octave.c -o my_octave

clean:
	rm -f $(TARGETS)

