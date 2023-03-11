# Copyright 2020 Darius Neatu <neatudarius@gmail.com>

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS=my_octave

build: $(TARGETS)

my_octave: octave.c functions.c
	$(CC) $(CFLAGS) octave.c functions.c -o my_octave
	
pack:
	zip -FSr 311CA_ArpasanuEmiliaOana_Tema2.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
